// Erich Viebrock
//
// COMP53 Fall 2012
//
// Brick.h
//
// Defines Brick objects for the Breakout game.

#ifndef BRICK_DOT_H
#define BRICK_DOT_H

#include<iostream>
#include "InterAct2D.h"

class Brick
{
public:
	// construct a brick
	Brick(float _center_x, float _center_y, float _width, float _height, Color _color);

	// destroy a brick - currently nothing to do.
	virtual ~Brick() { }

	// Draw brick at its current position.
	virtual void draw();
	
	// Get the current boundaries of the brick.
	virtual void getPosition(float& _left, float& _right, float& _top, float& _bottom) const;

	virtual float getXPosition(float& _left, float& _right) const;

	virtual float getYPosition(float& _top, float& _bottom) const;

	// return 1 for normal brick
	virtual int getName()
	{
		return 1;
	}

protected:
	Rect rectangle;
	float left, right, top, bottom;
};

#endif