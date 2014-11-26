// Erich Viebrock
//
// COMP53 Fall 2012
//
// PowerUpBrick.cpp
//
// Implements StrongBrick objects for the Breakout game.

#include "PowerUpBrick.h"
#include<iostream>

PowerUpBrick::PowerUpBrick(float _center_x, float _center_y, float _width, float _height) : Brick(_center_x, _center_y, _width, _height, gold)
{
	
}

// return 3 for power up brick
int PowerUpBrick::getName()
{
	return 3;
}