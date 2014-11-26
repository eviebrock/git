// Erich Viebrock
//
// COMP53 Fall 2012
//
// StrongBrick.cpp
//
// Implements StrongBrick objects for the Breakout game.

#include "StrongBrick.h"
#include<iostream>

StrongBrick::StrongBrick(float _center_x, float _center_y, float _width, float _height) : Brick(_center_x, _center_y, _width, _height, red)
{
	
}

// return 2 for strong brick
int StrongBrick::getName()
{
	return 2;
}