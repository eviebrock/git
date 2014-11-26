// InterAct2D.h
// Version 2.0 Beta released Nov 21, 2012

#ifndef INTERACT2D_DOT_H
#define INTERACT2D_DOT_H
#include <time.h>     // used by RandomGenerator for seed
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  some useful constants, functions and objects
///////////////////////////////////////////////////////////////////////////

#define PI 3.1415f
inline float deg2rad(float deg) { return deg*PI/180.0f; }
inline float rad2deg(float rad) { return rad*180.0f/PI; }

// convert any object with operator<< defined to a string
template <class T>
inline string toString(T x)
{ stringstream ss; ss << x;	return ss.str(); }

// output stream attached to file system_log.txt
extern ofstream logout;

///////////////////////////////////////////////////////////////////////////
//  class Point
///////////////////////////////////////////////////////////////////////////

class Point
{
public:
	Point() : x(0.0), y(0.0) { }
	Point(float _x, float _y) : x(_x), y(_y) { }
	Point(const Point& _p) : x(_p.x), y(_p.y) { }
	Point& operator=(const Point& _p) { x = _p.x; y = _p.y; return *this; }

	float getX() const { return x; }
	float getY() const { return y; }

	void moveTo(const Point& _p) { x = _p.x; y = _p.y; }
	void move(float _dx, float _dy) { x += _dx; y += _dy; }

private:
	float x, y;
};

///////////////////////////////////////////////////////////////////////////
//  class Event
///////////////////////////////////////////////////////////////////////////

class Event
{
public:
	bool restart;
	bool repaint;
	float elapsed_time_msec;

	long screen_width;
	long screen_height;

	bool key_pressed;
	bool key_released;
	char key;

	Point mouse_position;
	bool mouse_is_valid;
	bool mouse_left_click;
	bool mouse_right_click;
	bool mouse_moved;
	Event()
		: restart(false), repaint(false), elapsed_time_msec(0.0f),
		  screen_width(100), screen_height(100), key_pressed(false), key_released(false),
		  mouse_is_valid(false), mouse_left_click(false), mouse_right_click(false), mouse_moved(false)
	{ }
};

///////////////////////////////////////////////////////////////////////////
//  class Color
///////////////////////////////////////////////////////////////////////////

class Color
{
private:
	// Colors are stored internally as floats in range [0.0->1.0]
	// for compatibility with openGL.
	// General constructors for Colors expect (unsigned char) integers
	// in range [0->255] then convert to floats for storage
	float c[4];
	float& r;
	float& g;
	float& b;
	float& a;

public:
	// default constructor
	Color() : r(c[0]), g(c[1]), b(c[2]), a(c[3])
	{ r = g = b = a = 1.0f; }

	// general constructor - integers in range [0->255]
	Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char  _a=255)
		: r(c[0]), g(c[1]), b(c[2]), a(c[3])
	{ r = float(_r)/255.0f; g = float(_g)/255.0f; b = float(_b)/255.0f; a = float(_a)/255.0f; }

	// copy constructor
	Color(const Color& _other) : r(c[0]), g(c[1]), b(c[2]), a(c[3])
	{ r = _other.r; g = _other.g; b = _other.b; a = _other.a; }

	// assignment operator
	Color& operator=(const Color& _rhs)
	{
	    r = _rhs.r; g = _rhs.g; b = _rhs.b; a = _rhs.a;
		return *this;
	}

	// equality test
	bool operator==(const Color &rhs)
	{ return (r==rhs.r) && (g==rhs.g) && (b==rhs.b) && (a==rhs.a);	}

	// accessors
	float redf()   { return r; }
	float greenf() { return g; }
	float bluef()  { return b; }
	float alphaf() { return a; }
	unsigned char red()   { return (unsigned char)(r*255); }
	unsigned char green() { return (unsigned char)(g*255); }
	unsigned char blue()  { return (unsigned char)(b*255); }
	unsigned char alpha() { return (unsigned char)(a*255); }
};

const Color white    (0xff, 0xff, 0xff);
const Color blue     (0x00, 0x00, 0xf0);
const Color teal     (0x00, 0x80, 0x80);
const Color green    (0x00, 0xc0, 0x00);
const Color turquoise(0x43, 0xc6, 0xdb);
const Color darkgray (0x7a, 0x7a, 0x7a);
const Color brown    (0x98, 0x05, 0x17);
const Color purple   (0xa4, 0x00, 0xd7);
const Color lightblue(0xb5, 0xda, 0xff);
const Color lightgray(0xdc, 0xdc, 0xdc);
const Color gold     (0xd4, 0xa0, 0x17);
const Color red      (0xff, 0x00, 0x00);
const Color orange   (0xf8, 0x7a, 0x17);
const Color pink     (0xfa, 0xaf, 0xbe);
const Color yellow   (0xff, 0xff, 0x00);
const Color black    (0x00, 0x00, 0x00);

///////////////////////////////////////////////////////////////////////////
//  class Shape
///////////////////////////////////////////////////////////////////////////

class Shape
{
public:

	Shape()
		: p1(), p2(),
		  fill_color(darkgray), outline_color(darkgray),
		  pen_width(1), filled(true)
	{ }

	Shape(const Point& _p1)
		: p1(_p1), p2(_p1),
		  fill_color(darkgray), outline_color(darkgray),
		  pen_width(1), filled(true)
	{ }

	Shape(const Point& _p1, const Point& _p2)
		: p1(_p1), p2(_p2),
		  fill_color(darkgray), outline_color(darkgray),
		  pen_width(1), filled(true)
	{ }

	Shape(const Point& _p1, float _x_size, float _y_size)
		: fill_color(darkgray), outline_color(darkgray),
		  pen_width(1), filled(true)
	{
		float half_x_size = _x_size/2.0f;
		float half_y_size = _y_size/2.0f;
		float center_x = _p1.getX();
		float center_y = _p1.getY();
		p1 = Point(center_x-half_x_size, center_y-half_y_size);
		p2 = Point(center_x+half_x_size, center_y+half_y_size);
	}

	// virtual destructor may be necessary for derived classes
	virtual ~Shape() { }

	// member functions to access/modify position and shape

	virtual float getXSize() { return p2.getX()-p1.getX(); }
	virtual float getYSize() { return p2.getY()-p1.getY(); }

	virtual Point getP1() { return p1; }
	virtual Point getP2() { return p2; }

	virtual void setP1(const Point& _p1) { p1 = _p1; }
	virtual void setP2(const Point& _p2) { p2 = _p2; }

	virtual Point getCenter()
	{
		return Point((p1.getX()+p2.getX())/2.0f, (p1.getY()+p2.getY())/2.0f);
	}

	virtual void moveTo(const Point& _p)
	{
		Point center = getCenter();
		move(_p.getX()-center.getX(), _p.getY()-center.getY());
	}

	virtual void move(float _dx, float _dy)
	{
		p1.move(_dx, _dy);
		p2.move(_dx, _dy);
	}

	// member functions to access/modify drawing characteristics

	virtual Color getFillColor() const { return fill_color; }
	virtual void  setFillColor(const Color& _color) { fill_color = _color; }

	virtual Color getOutlineColor() const { return outline_color; }
	virtual void  setOutlineColor(const Color& _color) { outline_color = _color; }

	virtual short getPenWidth() { return pen_width; }
	virtual void  setPenWidth(short _w) { pen_width = _w; }

	virtual void setFilled() { filled = true; }
	virtual void setOutline() { filled = false; }

	// virtual functions that must be implemented by subclasses
	virtual void draw()=0;

protected:
	// locations
	Point p1, p2;
	// color of the shape
	Color fill_color;
	Color outline_color;
	short pen_width;
	bool filled;
};

///////////////////////////////////////////////////////////////////////////
//  class Oval
///////////////////////////////////////////////////////////////////////////

class Oval : public Shape
{
public:
	Oval() : Shape() {}
	Oval(const Point& _p1, float _x_size, float _y_size)
		: Shape(_p1, _x_size, _y_size) { }

	virtual void draw();
};

///////////////////////////////////////////////////////////////////////////
//  class Rectangle
///////////////////////////////////////////////////////////////////////////

class Rect : public Shape
{
public:
	Rect() : Shape() {}
	Rect(const Point& _p1, float _x_size, float _y_size)
		: Shape(_p1, _x_size, _y_size) { }

	virtual void draw();
};

///////////////////////////////////////////////////////////////////////////
//  class Line
///////////////////////////////////////////////////////////////////////////

class Line: public Shape
{
public:
	Line()	: Shape() { }

	Line(const Point& _p1, const Point& _p2) : Shape(_p1, _p2)	{ }

	const float getLength()
	{
		float dx = p1.getX()-p1.getX(), dy = p2.getY()-p1.getY();
		return sqrt(dx*dx + dy*dy);
	}

	virtual void draw();
};

///////////////////////////////////////////////////////////////////////////
//  class Text
///////////////////////////////////////////////////////////////////////////

class Text: public Shape
{
public:
	Text()	: Shape(), center(), text("") { }

	Text(const Point& _p1, const string& s ="")
		: Shape(_p1), center(_p1)
	{
		setText(s);
	}

	virtual Point getCenter() {	return center; }

	virtual void moveTo(const Point& _p)
	{
		move(_p.getX()-center.getX(), _p.getY()-center.getY());
		recomputeBoundary();
	}

	virtual void move(float _dx, float _dy)
	{
		center.move(_dx, _dy);
		recomputeBoundary();
	}

	string getText() const { return text; }

	void setText(const string& s)
	{
		text = s;
		recomputeBoundary();
	}

	virtual void draw();

private:
	Point center;
	string text;
	void recomputeBoundary();
};

///////////////////////////////////////////////////////////////////////////
//  class Image
///////////////////////////////////////////////////////////////////////////

class Image : public Shape
{
public:
	Image()
		: Shape(), filename("UNDEFINED"), use_transparency(false),
		  image_loaded(false), load_failure_count(0), texture_index(-1)
	{ }

	Image(const Point& _p1, string _file)
		: Shape(_p1), filename(_file), use_transparency(false),
		  image_loaded(false), load_failure_count(0), texture_index(-1)
	{ }

	Image(const Point& _p1, string _file, unsigned char _transparent_color[3])
		: Shape(_p1), filename(_file), use_transparency(false),
		  image_loaded(false), load_failure_count(0), texture_index(-1)
	{
		transparent_color[0] = _transparent_color[0];
		transparent_color[1] = _transparent_color[1];
		transparent_color[2] = _transparent_color[2];
	}

	virtual void draw();

private:
	string filename;
	unsigned char transparent_color[3];
	bool use_transparency;
	bool image_loaded;
	short load_failure_count;
	short texture_index;

	void loadImage();
};

///////////////////////////////////////////////////////////////////////////
//  class RandomGenerator
///////////////////////////////////////////////////////////////////////////

class RandomGenerator
{
public:

	RandomGenerator(unsigned long seed = 0)
	{
		if (seed == 0) srand((unsigned int)time(0));
	}

	// generate a random integer between 0 and range-1, inclusive
	unsigned short random(unsigned short range)
	{
		return (unsigned short)(range*frandom());
	}

	// generate a random real number between 0.0 and 1.0, inclusive
	float frandom()
	{
		return float(rand())/float(RAND_MAX);
	}
};

#endif   // INTERACT2D_DOT_H
