// Erich Viebrock
//
// COMP53 Fall 2012
//
// StrongBrick.h
//
// Defines StrongBrick objects for the Breakout game.

#ifndef STRONGBRICK_DOT_H
#define STRONGBRICK_DOT_H

#include "InterAct2D.h"
#include "Brick.h"

class StrongBrick : public Brick
{
public:
	// construct a brick
	StrongBrick(float _center_x, float _center_y, float _width, float _height);//, short _health);

	int getName();

protected:
	short health;
};

#endif
