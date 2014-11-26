// Erich Viebrock
//
// COMP53 Fall 2012
//
// PowerUpBall.cpp
//
// Implements Ball objects for the Breakout game.

#include "PowerUpBall.h"

PowerUpBall::PowerUpBall(float _center_x, float _center_y, float _radius, float _speed_x, float _speed_y, Color _color)	: Ball(_center_x, _center_y, _radius, _speed_x, _speed_y, gold)
{ 

}

// return 2 for power up ball
int PowerUpBall::getName()
{
	return 2;
}