// Erich Viebrock
//
// COMP53 Fall 2012
//
// PowerUpBall.h
//
// Defines Ball objects for the Breakout game.

#ifndef POWERUPBALL_DOT_H
#define POWERUPBALL_DOT_H
#include "InterAct2D.h"
#include "Ball.h"

class PowerUpBall : public Ball
{
public:
	// Create a  Ball.
	PowerUpBall(float _center_x=0.0, float _center_y=0.0, float _radius=0.0, float _speed_x=0.0, float _speed_y=0.0, Color _color=black);

	// Used for ball type detection
	int getName();
	
	// Destroy a Ball - currently nothing to do
	//virtual ~PowerUpBall() { }

protected:
	//Oval circle;
	//float x_position, y_position, radius;
	//float x_velocity, y_velocity;
};

#endif
