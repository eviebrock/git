// Erich Viebrock
//
// COMP53 Fall 2012
//
// PowerUpBrick.h
//
// Defines PowerUpBrick objects for the Breakout game.

#ifndef POWERUPBRICK_DOT_H
#define POWERUPBRICK_DOT_H

#include "InterAct2D.h"
#include "Brick.h"
//#include "Ball.h"

class PowerUpBrick : public Brick
{
public:
	// construct a brick
	PowerUpBrick(float _center_x, float _center_y, float _width, float _height);

	int getName();

protected:

};

#endif
