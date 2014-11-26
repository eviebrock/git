// InterAct2D.cpp
// Version 2.0 Beta released Nov 21, 2012

/* Pre-defined compiler macros
__APPLE__  defined by OSX
_WIN32     defined by 32-bit and 64-bit Windows
__GNUC__   defined by GNU C/C++ compiler
_MSC_VER   defined by Visual C++
*/
#if defined(__APPLE__)   // OSX convention
#include <GLUT/glut.h>
#elif defined(_WIN32)    // Windows
#include <windows.h>
#include <GL/glut.h>
#else                    // anything else
#include <GL/glut.h>
#endif

#include "InterAct2D.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <ctime>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Function to pass events back to the application.
//  The handleEvent() function is called whenever an event occurs.
//  Events can occur from:
//    keyboard key press or release
//    mouse clicks or motion
//    game timer (every 30 msec)
//    repaint/redraw events
//  The application code MUST implement this function.
///////////////////////////////////////////////////////////////////////////
extern void handleEvent(Event);

//=========================================================
//============ Internal Exception =========================
//=========================================================

class InterAct2DException
{
public:
	InterAct2DException() : msg("Unspecified exception") { }
	InterAct2DException(const string& _msg) : msg(_msg) { }
	string msg;
};

//=========================================================
//============ System Log =================================
//=========================================================

ofstream logout;

class SystemLog
{
public:
	SystemLog() { logout.open("system_log.txt"); }
	~SystemLog()
	{
		if (logout)
		{
			logout << "Log closed normally" << endl;
			logout.close();
		}
	}
};

// global instance of SystemLog forces constructor to be
// called during program startup and causes the destructor
// to be called during program shutdown.
SystemLog system_log;

//=========================================================
//============ Texture (BMP) Support ======================
//=========================================================

typedef short TextureID;

//----- class TextureManager ------------------------------

class TextureManager
{

public:
	TextureManager();
	virtual ~TextureManager();

	TextureID makeTextureFromBMP(const char* filename);
	TextureID makeTextureFromBMP(const char* filename, unsigned char alphacolor[3], bool use_alpha=false);
	TextureID findTextureByFilename(const char* filename);

	void releaseTexture(TextureID tid);
	void releaseAllTextures();

	bool selectTexture(TextureID tid);
	bool deselectTexture(TextureID tid);

	bool getImageSize(TextureID tid, long& width, long& height);
};

//----- class Texture -------------------------------------

/*
The texture class and the BMP reader are inspired by code by Dan Cliburn.
Dan's code was based in turn on Nate Miller's 5/5/1999 texture mapping code:
http://www.essi.fr/~buffa/cours/synthese_image/DOCS/Tutoriaux/Nate/index-6.htm,
and tha alpha replacement technique by Kevin Hawkins and Dave Astle:
"OpenGL Game Programming", by , pages 434-438.
*/

class Texture
{
private:
	GLuint tex_name; // The GL texture name
	string filename;
	long image_width;
	long image_height;
	bool using_alpha;
	unsigned long num_pixels;
	bool valid;

public:
	Texture(GLuint _tex_name, const char* _file)
		: tex_name(_tex_name), filename(_file), image_width(0), image_height(0),
		  using_alpha(false),  valid(false)
	{
		unsigned char alphacolor[3];
		readBMP(_file, alphacolor, false);
	}

	Texture(GLuint _tex_name, const char* _file, unsigned char alphacolor[3])
		: tex_name(_tex_name), filename(_file), image_width(0), image_height(0),
		  using_alpha(false),  valid(false)
	{
		readBMP(_file, alphacolor, true);
	}

	virtual ~Texture()   { glDeleteTextures(1, &tex_name); }
	GLuint getTexName()  { return tex_name; }
	string getFilename() { return filename; }
	short  getWidth()    { return image_width; }
	short  getHeight()   { return image_height; }
	bool   isValid()     { return valid; }
	void   disable()     { glDisable(GL_TEXTURE_2D); }
	void   enable()      { setTextureParameters(); glEnable(GL_TEXTURE_2D); }

private:

	bool readBMP(const char* fileName, unsigned char alphacolor[3], bool use_alpha)
	{
		unsigned char* image_data_RGB = NULL;
		unsigned char* image_data_RGBA = NULL;
		unsigned char* data_to_load = NULL;
		FILE* fp = NULL;
#ifdef _MSC_VER
		errno_t err = fopen_s(&fp, fileName, "r");
		if (err != 0) fp = NULL;
#else
		fp = fopen(fileName, "r");
		if (fp == NULL) return false;
#endif
		if (fp == NULL)
		{
			logout << "could not open bitmap: " << fileName << endl;
			valid = false;
			return false;
		}
		image_width = readLong(fp, 18);
		image_height = readLong(fp, 22);

		unsigned long data_offset = 55;
		unsigned short bits_per_pixel = readShort(fp, 28);
		if (bits_per_pixel != 24) // this should eventually be fixed
		{
			logout << "invalid bitmap: " << fileName << " has " << bits_per_pixel << " bits per pixel" << endl;
			valid = false;
			return false;
		}
		unsigned short bytes_per_pixel = bits_per_pixel / 8;
		num_pixels = image_width*image_height;
		unsigned long byte_size = num_pixels*bytes_per_pixel;

		image_data_RGB = new unsigned char[byte_size];

		fseek(fp, data_offset, 0);
		unsigned char tmp_byte[3];
		short row_padding = (4 - (image_width*3)%4) % 4;
		long row, col;
		for (row=image_height-1; row>=0; row--)
		{
			for (col = 0; col<image_width; col++)
			{
				fread(tmp_byte, 1, 3, fp); // blue
				unsigned long baseix = (row*image_width+col)*3;
				image_data_RGB[baseix]   = tmp_byte[1]; // red
				image_data_RGB[baseix+1] = tmp_byte[0]; // green
				image_data_RGB[baseix+2] = tmp_byte[2]; // blue
			}
			for (int ii=0; ii<row_padding; ii++) fread(tmp_byte, 1, 1, fp);
		}
		fclose(fp);
		data_to_load = image_data_RGB;

		if (use_alpha)
		{
			image_data_RGBA = new unsigned char[num_pixels*((bits_per_pixel/8) + 1)];
			int newIndex = 0;
			for (unsigned long i = 0; i < num_pixels*(bits_per_pixel/8); i +=3)
			{
				// Copy the pixel data into the new array
				image_data_RGBA[newIndex] = image_data_RGB[i];
				image_data_RGBA[newIndex+1] = image_data_RGB[i+1];
				image_data_RGBA[newIndex+2] = image_data_RGB[i+2];
				// If the pixel color is the designated alph color, set the alpha to 0 (transparent).
				// Otherwise, set it to 255 (opaque).
				if ((image_data_RGB[i] == alphacolor[0]) && (image_data_RGB[i+1] == alphacolor[1]) &&
					(image_data_RGB[i+2] == alphacolor[2]))
					image_data_RGBA[newIndex+3] = 0;
				else
					image_data_RGBA[newIndex+3] = 0xFF;
				newIndex += 4;
			}
			data_to_load = image_data_RGBA;
			using_alpha = true;
		}

		loadToGraphics(data_to_load, using_alpha);

		if (image_data_RGB != NULL)  { delete [] image_data_RGB;  image_data_RGB = NULL;  }
		if (image_data_RGBA != NULL) { delete [] image_data_RGBA; image_data_RGBA = NULL; }

		valid = true;
		return valid;
	}

	unsigned long readLong(FILE* fp, long offset)
	{
		unsigned char bytes[4];
		fseek(fp, offset, 0);
		fread(bytes, 1, 4, fp);
		unsigned long x = (unsigned long)(bytes[0])
		                + (unsigned long)(bytes[1])*(unsigned long)(256)
			            + (unsigned long)(bytes[2])*(unsigned long)(6400)
						+ (unsigned long)(bytes[3])*(unsigned long)(1638400);
		return x;
	}

	unsigned short readShort(FILE* fp, long offset)
	{
		unsigned char bytes[2];
		fseek(fp, offset, 0);
		fread(bytes, 1, 2, fp);
		unsigned short x = (unsigned short)(bytes[0])
		                 + (unsigned short)(bytes[1])*(unsigned short)(256);
		return x;
	}

	void loadToGraphics(unsigned char* data, bool uses_alpha)
	{
		enable();
		glBindTexture(GL_TEXTURE_2D, tex_name);
		if (uses_alpha)
		{
			glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height,
				0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image_width, image_height,
				GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D,	0, GL_RGB, image_width, image_height,
				0, GL_RGB,	GL_UNSIGNED_BYTE, data);
		}
	}

	void setTextureParameters()
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, getTexName());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (using_alpha)
		{
			glEnable (GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}

};

//----- class TextureStorage ------------------------------

class TextureStorage
{
public:
	TextureStorage()
	{ }
	virtual ~TextureStorage()
	{ }

	GLuint getFreeTextureName()
	{
		if (available_texture_names.size() == 0) requestMoreTextureNames();
		GLuint tex_name = available_texture_names.front();
		available_texture_names.pop_front();
		return tex_name;
	}

	void requestMoreTextureNames()
	{
		GLuint texture_names[20];
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(20, texture_names);
		for (short i=0; i<20; i++) available_texture_names.push_back(texture_names[i]);
	}

	TextureID getFreeTextureID() { return next_id++; }

	void storeTexture(TextureID id, Texture* texture)
	{
		textures.insert(pair<TextureID, Texture*>(id, texture));
	}

	TextureID findByFilename(const char* filename)
	{
		map<TextureID, Texture*>::iterator iter = textures.begin();
		while (iter != textures.end())
		{
			if (iter->second->getFilename() == filename) return iter->first;
			iter++;
		}
		return -1;
	}

	Texture* getTexture(TextureID id)
	{
		map<TextureID, Texture*>::iterator iter = textures.find(id);
		if (iter == textures.end()) return NULL;
		return iter->second;
	}

	// releaseTexture() and releaseAllTextures() do not return
	//   the texture to OpenGL for release
	void releaseTexture(TextureID id)
	{
		map<TextureID, Texture*>::iterator iter = textures.find(id);
		if (iter == textures.end()) return;
		delete iter->second;
		textures.erase(iter);
	}

	void releaseAllTextures()
	{
		map<TextureID, Texture*>::iterator iter = textures.begin();
		while (iter != textures.end())
		{
			delete iter->second;
			textures.erase(iter++);
		}
	}
private:
	map<TextureID, Texture*> textures;
	list<GLuint> available_texture_names;
	TextureID next_id;
};

static TextureStorage texture_storage;

static TextureManager texture_manager;

//----- class TextureManager methods ----------------------

TextureManager::TextureManager() { }

TextureManager::~TextureManager() { texture_storage.releaseAllTextures(); }

void TextureManager::releaseAllTextures() {	texture_storage.releaseAllTextures(); }

void TextureManager::releaseTexture(TextureID tid) { texture_storage.releaseTexture(tid); }

bool TextureManager::getImageSize(TextureID tid, long& width, long& height)
{
	Texture* tex = texture_storage.getTexture(tid);
	if (tex == NULL) return false;
	width = tex->getWidth();
	height = tex->getHeight();
	return true;
}

TextureID TextureManager::findTextureByFilename(const char* filename)
{
	return texture_storage.findByFilename(filename);
}

TextureID TextureManager::makeTextureFromBMP(const char* filename)
{
	unsigned char alphacolor[3];
	return makeTextureFromBMP(filename, alphacolor, false);
}

TextureID TextureManager::makeTextureFromBMP(const char* filename,
	unsigned char alphacolor[3], bool use_alpha)
{
	TextureID tid = texture_storage.getFreeTextureID();
	GLuint texture_name = texture_storage.getFreeTextureName();
	Texture* new_texture;
	if (use_alpha)
		new_texture = new Texture(texture_name, filename, alphacolor);
	else
		new_texture = new Texture(texture_name, filename);
	if (!new_texture->isValid()) { delete new_texture; return -1; }
	texture_storage.storeTexture(tid, new_texture);
	return tid;
}

bool TextureManager::selectTexture(TextureID tid)
{
	Texture* tex = texture_storage.getTexture(tid);
	if (tex == NULL) return false;
	tex->enable();
	return true;
}

bool TextureManager::deselectTexture(TextureID tid)
{
	Texture* tex = texture_storage.getTexture(tid);
	if (tex == NULL) return false;
	tex->disable();
	return true;
}

//=========================================================
//============ Misc. OpenGL/GLUT functions ================
//=========================================================

/* Available fonts (http://www.opengl.org/resources/libraries/glut/spec3/node76.html)
  fixed-width:
    GLUT_BITMAP_8_BY_13
    GLUT_BITMAP_9_BY_15
  proportional:
    GLUT_BITMAP_TIMES_ROMAN_10
    GLUT_BITMAP_TIMES_ROMAN_24
    GLUT_BITMAP_HELVETICA_10
    GLUT_BITMAP_HELVETICA_12
    GLUT_BITMAP_HELVETICA_18
*/

#define GLUT_FONT_ID GLUT_BITMAP_9_BY_15
#define GLUT_FONT_HEIGHT 15

void renderString(float x, float y, float z, Color color, const char* string)
{
	glPushMatrix();		//save orientation of coordinate systems
	glLoadIdentity();
    glColor3f(color.redf(), color.greenf(), color.bluef());
	glRasterPos3f(x, y, z);
	for (short i = 0; string[i] != '\0'; i++) glutBitmapCharacter(GLUT_FONT_ID, string[i]);
	glPopMatrix();		//restore orientation of coordinate systems
}

bool checkOpenGLError(int placecode)
{
	GLenum error_code = glGetError();
	if (error_code != GL_NO_ERROR)
	{
		const GLubyte *errString;
		errString = gluErrorString(error_code);
		logout << "openGL error at " << placecode
			   << " error is " << error_code << " " << errString << endl;
		return true;
	}
	return false;
}

//=========================================================
//============ I2D Main Control ===========================
//=========================================================

#define I2D_BUTTON_HEIGHT 20
#define I2D_BUTTON_STEP 0
#define I2D_BUTTON_RUN 1
#define I2D_BUTTON_PAUSE 2
#define I2D_BUTTON_QUIT 3
#define I2D_BUTTON_RESTART 4

class I2DButton
{
public:
	I2DButton() {}
	I2DButton(const Point& _center, float _width, float _height,
		      const string& _label, short _command)
		: boundary(_center, _width, _height),
		  label(_center, _label)
	{
		boundary.setFillColor(lightgray);
		boundary.setOutlineColor(black);
		boundary.setPenWidth(3);
		label.setFillColor(black);
		label.setOutlineColor(black);
		command = _command;
	}
	void reshape(const Point& _center, float _width, float _height)
	{
		float half_width = _width/2;
		float half_height = _height/2;
		Point p1(_center.getX()-half_width, _center.getY()-half_height);
		Point p2(_center.getX()+half_width, _center.getY()+half_height);
		boundary.setP1(p1);
		boundary.setP2(p2);
		Point label_center(_center.getX(), _center.getY()-4);
		label.moveTo(label_center);
	}
	short checkHit(const Point& click)
	{
		if ((click.getX() >= boundary.getP1().getX()) &&
			(click.getX() <= boundary.getP2().getX()) &&
			(click.getY() >= boundary.getP1().getY()) &&
			(click.getY() <= boundary.getP2().getY()))
			return command;
		return -1;
	}
	void draw()
	{
		boundary.draw();
		label.draw();
	}
private:
	Rect boundary;
	Text label;
	short command;
};

class I2DControl
{
public:
    I2DControl()
		: initialized(false), first_update(true), clear_color(0.1f,0.1f,0.1f),
		  window_height(600), window_width(800), prev_app_time_msec(0.0),
		  paused(false), restart(false)
	{
		initializeButtons();
	}
	virtual ~I2DControl() { }
    void initialize(int argc, char **argv, int init_width, int init_height);
    bool isInitialized() { return initialized; }
	void run();
	void updateApplication(bool paused_step=false);
	void display();
	void timer();
	void reshape(int w, int h);
	void sendKeyClickEvent(char key);
	void sendKeyReleaseEvent(char key);
	void sendMouseClickEvent(int button, int state, float mouse_x, float mouse_y);
	void sendMouseMoveEvent(float mouse_x, float mouse_y);

private:
    bool initialized;
	bool first_update;
	Color clear_color;
	int window_height;
	int window_width;
	float prev_app_time_msec;
	// system buttons
	bool paused;
	bool restart;
	I2DButton buttons[5];
	void initializeButtons();
	void positionButtons();
	short checkButtons(const Point& click);
	void drawButtons();
	void processButton(short button_code);
	void unpause();
};

static I2DControl* sys_control=NULL;

//============ GLUT callbacks ===============

inline static void timerHandler(int value)
{ if (sys_control != NULL) sys_control->timer(); }

inline static void displayHandler()
{ if (sys_control != NULL) sys_control->display(); }

inline static void idleHandler()
{ /*if (sys_control != NULL) sys_control->display();*/ }

inline static void reshapeHandler(int w, int h)
{ if (sys_control != NULL) sys_control->reshape(w,h); }

inline static void mouseHandler(int button, int state, int x, int y)
{ if (sys_control != NULL) sys_control->sendMouseClickEvent(button, state, x, y); }

inline static void keyDownHandler(unsigned char key, int x, int y)
{ if (sys_control != NULL) sys_control->sendKeyClickEvent(key); }

inline static void keyUpHandler(unsigned char key, int x, int y)
{ if (sys_control != NULL) sys_control->sendKeyReleaseEvent(key); }

inline static void mouseMotionHander(int x, int y)
{ if (sys_control != NULL) sys_control->sendMouseMoveEvent(x,y); }

//============ end GLUT callbacks ===============

void I2DControl::initializeButtons()
{
	buttons[I2D_BUTTON_PAUSE] = I2DButton(Point(0,0), 0, 0, string("PAUSE"), I2D_BUTTON_PAUSE);
	buttons[I2D_BUTTON_RUN] = I2DButton(Point(0,0), 0, 0, string("RUN"), I2D_BUTTON_RUN);
	buttons[I2D_BUTTON_RESTART] = I2DButton(Point(0,0), 0, 0, string("RESTART"), I2D_BUTTON_RESTART);
	buttons[I2D_BUTTON_STEP] = I2DButton(Point(0,0), 0, 0, string("STEP"), I2D_BUTTON_STEP);
	buttons[I2D_BUTTON_QUIT] = I2DButton(Point(0,0), 0, 0, string("QUIT"), I2D_BUTTON_QUIT);
}

void I2DControl::positionButtons()
{
	if (!paused)
	{
		short button_width = window_width / 3;
		short button_height = I2D_BUTTON_HEIGHT;
		short x = button_width/2;
		short y = window_height - button_height/2;
		buttons[I2D_BUTTON_PAUSE].reshape(Point(x,y), button_width, button_height);
		x += button_width;
		buttons[I2D_BUTTON_RESTART].reshape(Point(x,y), button_width, button_height);
		x += button_width;
		buttons[I2D_BUTTON_QUIT].reshape(Point(x,y), button_width, button_height);
		// inactive
		buttons[I2D_BUTTON_STEP].reshape(Point(-1000,-1000), button_width, button_height);
		buttons[I2D_BUTTON_RUN].reshape(Point(-1000,-1000), button_width, button_height);
	}
	else
	{
		short button_width = window_width / 4;
		short button_height = I2D_BUTTON_HEIGHT;
		short x = button_width/2;
		short y = window_height - button_height/2;
		buttons[I2D_BUTTON_RUN].reshape(Point(x,y), button_width, button_height);
		x += button_width;
		buttons[I2D_BUTTON_RESTART].reshape(Point(x,y), button_width, button_height);
		x += button_width;
		buttons[I2D_BUTTON_STEP].reshape(Point(x,y), button_width, button_height);
		x += button_width;
		buttons[I2D_BUTTON_QUIT].reshape(Point(x,y), button_width, button_height);
		// inactive
		buttons[I2D_BUTTON_PAUSE].reshape(Point(-1000,-1000), button_width, button_height);
	}
}

void I2DControl::drawButtons()
{
	for (short i=0; i<5; i++) buttons[i].draw();
}

void I2DControl::sendKeyClickEvent(char key)
{
	Event event;
	event.screen_width = window_width;
	event.screen_height = window_height;
	event.key_pressed = true;
	event.key = key;
	handleEvent(event);
}

void I2DControl::sendKeyReleaseEvent(char key)
{
	Event event;
	event.screen_width = window_width;
	event.screen_height = window_height;
	event.key_released = true;
	event.key = key;
	handleEvent(event);
}

void I2DControl::sendMouseClickEvent(int button, int state, float mouse_x, float mouse_y)
{
	Event event;

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		short button_code = -1;
		// check if click intercepted by system button
		for (short i=0; i<5; i++)
		{
			short code = buttons[i].checkHit(Point(mouse_x, mouse_y));
			if (code != -1) { button_code = code; break; }
		}
		if (button_code == -1)
		{
			event.mouse_left_click = true;
		}
		else
		{
			processButton(button_code);
			return;
		}
	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
	{
		event.mouse_right_click = true;
	}
	else
	{
		// ignore anything that's not a mouse button click
		return;
	}
	event.screen_width = window_width;
	event.screen_height = window_height;
	event.mouse_is_valid = true;
	event.mouse_position = Point(mouse_x, mouse_y);
	handleEvent(event);
}

void I2DControl::sendMouseMoveEvent(float mouse_x, float mouse_y)
{
	Event event;
	event.screen_width = window_width;
	event.screen_height = window_height;
	event.mouse_is_valid = true;
	event.mouse_moved = true;
	event.mouse_position = Point(mouse_x, mouse_y);
	handleEvent(event);
}

void I2DControl::processButton(short button_code)
{
	if (button_code == I2D_BUTTON_RUN)
	{	unpause(); }
	else if (button_code == I2D_BUTTON_PAUSE)
	{	paused = true; }
	else if (button_code == I2D_BUTTON_STEP)
	{	if (paused) updateApplication(true); }
	else if (button_code == I2D_BUTTON_QUIT)
	{	exit(0); }
	else if (button_code == I2D_BUTTON_RESTART)
	{
		Event event;
		event.screen_width = window_width;
		event.screen_height = window_height;
		event.restart = true;
		handleEvent(event);
	}
}

void I2DControl::unpause()
{
	if (!paused) return;
	prev_app_time_msec = (((float)clock())/CLOCKS_PER_SEC)*1000.0;
	glutTimerFunc(30 /* msec */, timerHandler, 0);
	paused = false;
}

void I2DControl::updateApplication(bool paused_step)
{
	float elapsed_time;
	if (paused_step) elapsed_time = 30;
	else
	{
		float app_time_msec = (((float)clock())/CLOCKS_PER_SEC)*1000.0;
	    elapsed_time = app_time_msec - prev_app_time_msec;
		prev_app_time_msec = app_time_msec;
	}

	Event event;
	event.elapsed_time_msec = elapsed_time;

	event.screen_width = window_width;
	event.screen_height = window_height;

	if (first_update || restart)
	{
		event.restart = true;
		first_update = false;
		restart = false;
	}
	handleEvent(event);
}

void I2DControl::timer()
{
	updateApplication();
	if (!paused) glutTimerFunc(30 /* msec */, timerHandler, 0);
}

void I2DControl::display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho (0, window_width, window_height, 0, 0, 1);
    glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Event event;
	event.repaint = true;
	event.screen_width = window_width;
	event.screen_height = window_height;
	handleEvent(event);

	positionButtons();
	drawButtons();

	glutSwapBuffers();
	checkOpenGLError(203);
	glutPostRedisplay();
}

void I2DControl::reshape(int w, int h)
{
	glClear(GL_COLOR_BUFFER_BIT);
	window_width = w; window_height = h;
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void I2DControl::initialize(int argc, char **argv, int init_width, int init_height)
{
	initialized = false;
    window_width = init_width;
    window_height = init_height;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("InterAct2D");

	glClearDepth(1.0f);
	glClearColor(clear_color.redf(), clear_color.greenf(), clear_color.bluef(), 1.0);

	glutIgnoreKeyRepeat(true);
	glutKeyboardFunc(keyDownHandler);
	glutKeyboardUpFunc(keyUpHandler);
	glutMouseFunc(mouseHandler);
	glutMotionFunc(mouseMotionHander);
	glutPassiveMotionFunc(mouseMotionHander);

	glutReshapeFunc(reshapeHandler);
	glutDisplayFunc(displayHandler);
	glutIdleFunc(idleHandler);
	glutTimerFunc(30 /* msec */, timerHandler, 0);

	if (checkOpenGLError(202)) throw InterAct2DException(string("OpenGL error"));

	initialized = true;
}

void I2DControl::run()
{
	if (!initialized) throw InterAct2DException(string("Attempt to run uninitialized system"));
	glutMainLoop();
}

//=========================================================
//==== InterAct2D Interface Class Methods =================
//=========================================================

void Oval::draw()
{
    float x1 = p1.getX();
    float y1 = p1.getY();
    float x2 = p2.getX();
    float y2 = p2.getY();
    float xradius = (x2-x1)/2.0;
    float yradius = (y2-y1)/2.0;
    float centerx = (x1+x2)/2.0;
    float centery = (y1+y2)/2.0;

	if (filled) {
		// draw filled area
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(fill_color.redf(), fill_color.greenf(), fill_color.bluef());
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(centerx, centery);
        for(int i=0; i < 360; i++)
        {
			float degInRad = deg2rad(i);
            glVertex2f(centerx+cos(degInRad)*xradius, centery+sin(degInRad)*yradius);
        }
        glEnd();
    }
	// draw outline
    glColor3f(outline_color.redf(), outline_color.greenf(), outline_color.bluef());
	glLineWidth(pen_width);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i < 360; i++)
    {
		float degInRad = deg2rad(i);
        glVertex2f(centerx+cos(degInRad)*xradius, centery+sin(degInRad)*yradius);
    }
    glEnd();
}

void Rect::draw()
{
    if (filled)
	{
		// draw filled area
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(pen_width);
		glColor3f(fill_color.redf(), fill_color.greenf(), fill_color.bluef());
		glBegin(GL_QUADS);
		glVertex2f(p1.getX(), p1.getY());
		glVertex2f(p1.getX(), p2.getY());
		glVertex2f(p2.getX(), p2.getY());
		glVertex2f(p2.getX(), p1.getY());
		glEnd();
	}
	// draw outline
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(outline_color.redf(), outline_color.greenf(), outline_color.bluef());
    glBegin(GL_QUADS);
    glVertex2f(p1.getX(), p1.getY());
    glVertex2f(p1.getX(), p2.getY());
    glVertex2f(p2.getX(), p2.getY());
    glVertex2f(p2.getX(), p1.getY());
    glEnd();
}

void Line::draw()
{
	// draw outline
	glLineWidth(pen_width);
    glColor3f(fill_color.redf(), fill_color.greenf(), fill_color.bluef());
    glBegin(GL_LINES);
    glVertex2f(p1.getX(), p1.getY());
    glVertex2f(p2.getX(), p2.getY());
    glEnd();
}

void Text::draw()
{
	renderString(p1.getX(), p1.getY()+GLUT_FONT_HEIGHT, 0.0f, fill_color, text.c_str());
}

void Text::recomputeBoundary()
{
	float height = GLUT_FONT_HEIGHT;
	float width = 0;
	for (unsigned short i=0; i<text.length(); i++)
		width += glutBitmapWidth(GLUT_FONT_ID, text[i]);
	float half_dx = width/2.0;
	float half_dy = height/2.0;
	p1 = Point(center.getX()-half_dx, center.getY()-half_dy);
	p2 = Point(center.getX()+half_dx, center.getY()+half_dy);
}

void Image::loadImage()
{
	if (image_loaded) return;
	if (load_failure_count > 10) return;
	texture_index = texture_manager.makeTextureFromBMP(filename.c_str(),
		transparent_color, use_transparency);
	if (texture_index < 0) { load_failure_count++; return; }
	float center_x = (p2.getX() + p1.getX())/2;
	float center_y = (p2.getY() + p1.getY())/2;
	long width, height;
	if (texture_manager.getImageSize(texture_index, width, height))
	{
		long half_width = width/2;
		long half_height = height/2;
		p1.moveTo(Point(center_x-half_width, center_y-half_height));
		p2.moveTo(Point(center_x+half_width, center_y+half_height));
	}
	image_loaded = true;
}

void Image::draw()
{
    if (!image_loaded) loadImage();
	if (!image_loaded)
	{
		Rect orangerect(p1, 10.0f, 10.0f);
		orangerect.setFillColor(orange);
		orangerect.setOutlineColor(orange);
		return;
	}
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();
	texture_manager.selectTexture(texture_index);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(p1.getX(), p1.getY());
    glTexCoord2f(0,1);
    glVertex2f(p1.getX(), p2.getY());
    glTexCoord2f(1,1);
    glVertex2f(p2.getX(), p2.getY());
    glTexCoord2f(1,0);
    glVertex2f(p2.getX(), p1.getY());
    glEnd();
	texture_manager.deselectTexture(texture_index);
	glPopMatrix();
}

//=========================================================
//============ MAIN =======================================
//=========================================================

int main(int argc, char** argv)
{
	try
	{
	    sys_control = new I2DControl;
	    if (sys_control != NULL)
	    {
            sys_control->initialize(argc, argv, 800, 600);
            sys_control->run();
	    }
	}
	catch (InterAct2DException& exception)
	{
		cerr << "InterAct2D exception encountered. See system_log.txt for details." << endl;
		logout << "Terminal InterAct2D exception:" << endl;
		logout << exception.msg <<endl;
		return 1;
	}

	return 0;
}