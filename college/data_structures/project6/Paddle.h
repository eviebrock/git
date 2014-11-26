// COMP53 Fall 2012
//
// Paddle.h
//
// Defines Paddle objects for the Breakout game.

#ifndef PADDLE_DOT_H
#define PADDLE_DOT_H

#include "InterAct2D.h"

class Paddle
{
public:
	// construct a Paddle
	Paddle(float _center_x=0.0, float _center_y=0.0,
		float _width=0.0, float _height=0.0,
		Color _color=black);

	// destroy a Paddle - currently nothing to do
	virtual ~Paddle() { }

	// Draw paddle at current position.
	virtual void draw();

	// Move paddle forward in time, based on current velocity.
	// Stop paddle from moving based walls as defined by range values (x-coordinates).
	// As the paddle moves, it slows down to simulate friction.
	virtual void move(float _delta_time_sec, float _range_top, float _range_bottom);

	// Accelerate the paddle to the left.
	void leftThrust();

	// Accelerate the paddle to the left.
	virtual void rightThrust();
	
	// Get the current horizontal velocity of the paddle (pixels/sec)
	virtual float getSpeed() const;

	// Get the current boundaries of the paddle.
	virtual void getPosition(float& _left, float& _right, float& _top, float& _bottom) const;

protected:
	Rect rectangle;
	float left, right, top, bottom, width;
	float velocity;
};

#endif