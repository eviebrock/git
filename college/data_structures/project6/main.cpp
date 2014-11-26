// Erich Viebrock
//
// COMP 135 - Spring 2013
//
// main.cpp
//
// Application control code for Pong game.
#include<iostream>
#include "InterAct2D.h"

// Standard Template Library
#include <list>
using namespace std;

// pong game objects
#include "Brick.h"
#include "paddle.h"
#include "clock.h"
#include "ball.h"
#include "StrongBrick.h"
#include "PowerUpBrick.h"
#include "PowerUpBall.h"
#include "ScoreBoard.h"

///////////////////////////////////////////////////////////////////////////
// class pong - controller class for game
///////////////////////////////////////////////////////////////////////////

class Pong
{
public:
	Pong();
	~Pong();

	// single public method to respond to all events
	void handleEvent(Event event);

private:
	// level countdown timer
	float remaining_time;

	// game objects
	list<Brick*> bricks;
	list<Ball*> balls;
	Paddle* paddle;
	Clock* clock;
	ScoreBoard* scoreboard;
	Ball* ball;

	// game control signals
	bool game_ready;
	bool left_key_pressed;
	bool right_key_pressed;

	// primary event response methods
	void drawGame(Event event);
	void startGame(Event event);
	void updateGame(Event event);
	void processUserInput(Event event);

	// secondary methods for specific tasks
	void draw_background(Event event);
	void draw_clock(Event event);
	void createBricks(Event event);
	void createPaddle(Event event);
	void createClock(Event event);
	void createScoreBoard(Event event);
	void createBall(Event event);
	void detectCollisions(Event event);
	void destroyGame();
};

///////////////////////////////////////////////////////////////////////////
// class Pong: constructor and destructor
///////////////////////////////////////////////////////////////////////////

Pong::Pong()
	: paddle(NULL), clock(NULL), game_ready(false),
      left_key_pressed(false), right_key_pressed(false), scoreboard(NULL)
{}

Pong::~Pong()
{
	destroyGame();
}

///////////////////////////////////////////////////////////////////////////
// class Pong: public member functions
///////////////////////////////////////////////////////////////////////////

void Pong::processUserInput(Event event)
{
	if (event.key_pressed && ((event.key == 'z') || (event.key == 'Z')))
		left_key_pressed = true;
	if (event.key_released && ((event.key == 'z') || (event.key == 'Z')))
		left_key_pressed = false;
	if (event.key_pressed && ((event.key == 'x') || (event.key == 'X')))
		right_key_pressed = true;
	if (event.key_released && ((event.key == 'x') || (event.key == 'X')))
		right_key_pressed = false;
}

void Pong::updateGame(Event event)
{
	// if time has passed, update the world
	float elapsed_time_sec = event.elapsed_time_msec/1000.0f;
	if (elapsed_time_sec > 0.0) //0.05f?
	{
		remaining_time -= elapsed_time_sec;
		if (remaining_time < 0.0) remaining_time = 0.0;
		if (left_key_pressed) paddle->leftThrust();
		if (right_key_pressed) paddle->rightThrust();
		clock->changeTo(remaining_time);
		//scoreboard->changeTo(remaining_time);

		// update moving objects
		paddle->move(elapsed_time_sec, 0.0f, float(event.screen_width));
		
		list<Ball*>::iterator ball_iter;
		ball_iter = balls.begin();
		while (ball_iter != balls.end())
		{
			(*ball_iter)->move(elapsed_time_sec);
			ball_iter++;
		}
		
		detectCollisions(event);
	}
}

void Pong::startGame(Event event)
{
	// delete any previous game
	destroyGame();
	// reset all game objects
	remaining_time = 300.0;  // 300 seconds = 5 minutes

	// create game objects
	//createBricks(event);
	createPaddle(event);
	createClock(event);
	createScoreBoard(event);
	createBall(event);
	game_ready = true;
}

void Pong::drawGame(Event event)
{
	// clear the game screen
	draw_background(event);
	// draw all objects
	list<Brick*>::iterator brick_iter;
	for (brick_iter = bricks.begin(); brick_iter != bricks.end(); brick_iter++)
		(*brick_iter)->draw();
	paddle->draw();
	clock->draw();
	scoreboard->draw();
	
	list<Ball*>::iterator ball_iter = balls.begin();
	while (ball_iter != balls.end())
	{
		(*ball_iter)->draw();
		ball_iter++;
	}
}

///////////////////////////////////////////////////////////////////////////
// class Pong: miscellaneous private member functions
///////////////////////////////////////////////////////////////////////////

void Pong::detectCollisions(Event event)
{
	list<Ball*>::iterator ball_iter = balls.begin();
	list<Brick*>::iterator brick_iter = bricks.begin();
	while (ball_iter != balls.end())
	{
		float ball_r = (*ball_iter)->getRadius();
		Point ball_pos = (*ball_iter)->getPosition();
		float ball_x = ball_pos.getX();
		float ball_y = ball_pos.getY();
		float ball_min_x = ball_x - ball_r;
		float ball_max_x = ball_x + ball_r;
		float ball_min_y = ball_y - ball_r;
		float ball_max_y = ball_y + ball_r;

		// check for collisions with walls
		if (ball_min_x < 0.0) (*ball_iter)->collision(false, true, false, false);
		if (ball_max_x > event.screen_width) (*ball_iter)->collision(true, false, false, false);
		// ***add implementation for deleting lives here***
		if (ball_min_y < 0.0) 
		{
			(*ball_iter)->collision(false, false, false, true);
		}
		if (ball_max_y > event.screen_height) (*ball_iter)->collision(false, false, true, false);
		// check for collision with paddle
		float paddle_left, paddle_right, paddle_top, paddle_bottom;
		paddle->getPosition(paddle_left, paddle_right, paddle_top, paddle_bottom);
		
		Ball* ball = (*ball_iter);
		srand(time(NULL));
		if ((ball_x >= paddle_left) && (ball_x <= paddle_right) && (ball_max_y >= paddle_top))
		{
			if(ball->getName() == 1)
			{
				// invert vertical speed
				(*ball_iter)->collision(false, false, true, false);
				// change horizontal speed based on paddle speed
				(*ball_iter)->addHorizontalSpeed(paddle->getSpeed()*0.1f);

			}
			
			else if(ball->getName() == 2)
			{
				int randNum = rand() % 4 + 1;
				delete (*ball_iter);
				balls.erase(ball_iter--);
				if (randNum == 1)
				{
					brick_iter = bricks.end();
					brick_iter--;
					for (int i=0; i<9; i++)
					{
						delete (*brick_iter);
						bricks.erase(brick_iter--);
						scoreboard->updateScore();
					}
				}
				else
				{
					createBall(event);
				}
			}
		}
		// check for ball/Brick collisions
		list<Brick*>::iterator brick_iter = bricks.begin();
		while (brick_iter!=bricks.end())
		{
			Brick* brick = (*brick_iter);
			float brick_left, brick_right, brick_top, brick_bottom;
			brick->getPosition(brick_left, brick_right, brick_top, brick_bottom);

			// if ball touches a brick
			// bottom
			if ((ball_x > brick_left) && (ball_x < brick_right) &&
				(ball_y > brick_top) && (ball_y < brick_bottom))
			{
				(*ball_iter)->collision(false, false, false, true);
				if (brick->getName() == 1)
				{
					delete (*brick_iter);
					bricks.erase(brick_iter++);
					scoreboard->updateScore();
				}
				else if (brick->getName() == 2)
				{
					// unbreakable brick
					brick_iter++;
				}
				else if (brick->getName() == 3)
				{
					float ball_size = 10.0f;
					float x_speed = 0.0f;
					float y_speed = 100.0f;
					Ball* new_power_up_ball = new PowerUpBall(brick->getXPosition(brick_left, brick_right), brick->getYPosition(brick_top, brick_bottom), ball_size, x_speed, y_speed, green);
					balls.push_back(new_power_up_ball);
					delete (*brick_iter);
					bricks.erase(brick_iter++);	
					scoreboard->updateScore();
				}
			}
			else
			{
				brick_iter++;
			}
		}
		ball_iter++;
	}
}

void Pong::draw_background(Event event)
{
	// Draw a rectangle to clear the game screen.
	Rect background(Point(event.screen_width/2.0f, event.screen_height/2.0f),
		float(event.screen_width), float(event.screen_height));
	background.draw();
}

///////////////////////////////////////////////////////////////////////////
// class Pong: private member functions for creating game objects
///////////////////////////////////////////////////////////////////////////


void Pong::createBricks(Event event)
{
	bricks.clear();

	short rows = 10;
	short columns = 9;

	// create a grid of Bricks, evenly spaced
	// across the top half of the screen

	float x_spacing = event.screen_width / 9.0f;
	float y_spacing = event.screen_height / 20.0f;
	float brick_width = x_spacing * 0.95f;
	float brick_height = y_spacing * 0.9f;
	float x, y;

	y = y_spacing;
	srand(time(NULL));
	for (int row = 0; row < rows; row++)
	{
		x = x_spacing/2.0f;
		for (int column = 0; column < columns; column++)
		{
			int randNum = rand() % 10 + 1;
			if (randNum == 1)
			{
				Brick* new_power_up_brick = new PowerUpBrick(x, y, brick_width, brick_height);
				bricks.push_back(new_power_up_brick);
				x += x_spacing;
			}
			else if (randNum == 10)
			{
				Brick* new_strong_brick = new StrongBrick(x, y, brick_width, brick_height);
				bricks.push_back(new_strong_brick);
				x += x_spacing;
			}
			else
			{
				Brick* new_brick = new Brick(x, y, brick_width, brick_height, blue);
				bricks.push_back(new_brick);
				x += x_spacing;
			}
		}
		y += y_spacing;
	}

}

void Pong::createPaddle(Event event)
{
	float x_center = event.screen_width - 50.0f;
	float y_center = event.screen_height / 2.0f;
	float paddle_width = 30.0f;
	float paddle_height = 100.0f;

	paddle = new Paddle(x_center, y_center, paddle_width, paddle_height, purple);
}

void Pong::createBall(Event event)
{
	float x_center = event.screen_width / 2.0f;
	float y_center = event.screen_height/ (2.0f) + 20.0f;
	float ball_size = 10.0f;
	float x_speed = 100.0f;
	float y_speed = 0.0f;

	Ball* new_ball = new Ball(x_center, y_center, ball_size, x_speed, y_speed, green);
	balls.push_back(new_ball);
}

void Pong::createClock(Event event)
{
	float x_position = 0.0f;
	float y_position = event.screen_height - 40.0f;

	clock = new Clock(x_position, y_position, remaining_time, yellow, darkgray);
}


void Pong::createScoreBoard(Event event)
{
	float x_position = event.screen_width - 200.0f;
	float y_position = event.screen_height - 40.0f;

	scoreboard = new ScoreBoard(x_position, y_position, remaining_time, white, darkgray);
}


void Pong::destroyGame()
{
	if (clock != NULL) delete clock; clock = NULL;
	balls.clear();
	if (paddle != NULL) delete paddle; paddle = NULL;
	list<Brick*>::iterator brick_iter;
	for (brick_iter = bricks.begin(); brick_iter != bricks.end(); brick_iter++)
		if ((*brick_iter) != NULL) delete (*brick_iter);
	bricks.clear();
	game_ready = false;
}

///////////////////////////////////////////////////////////////////////////
// Global Pong object that controls the game.
///////////////////////////////////////////////////////////////////////////

Pong pong_game;

///////////////////////////////////////////////////////////////////////////
// Callback function from InterAct2D that drives the game.
///////////////////////////////////////////////////////////////////////////

void Pong::handleEvent(Event event)
{
	if (event.restart) startGame(event);

	// wait for a restart event to initialize the game before
	// processing any other events.
	if (!game_ready) return;

	// these methods check for appropriate events
	// so they should always be called
	pong_game.processUserInput(event);
	pong_game.updateGame(event);

	// repaint event means to redraw entire screen
	if (event.repaint) drawGame(event);
}

// call back function just passes event to the game
void handleEvent(Event event)
{
	pong_game.handleEvent(event);
}