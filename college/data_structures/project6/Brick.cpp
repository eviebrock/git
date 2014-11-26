// Erich Viebrock
//
// COMP53 Fall 2012
//
// Brick.cpp
//
// Implements Brick objects for the Breakout game.

#include "Brick.h"
#include<iostream>

Brick::Brick(float _center_x, float _center_y, float _width, float _height,
			 Color _color)
:	rectangle(Point(_center_x, _center_y), _width, _height),
	left(_center_x - _width/2.0f), right(_center_x + _width/2.0f), 
	top(_center_y - _height/2.0f), bottom(_center_y + _height/2.0f)
{
	rectangle.setFillColor(_color);
	rectangle.setOutlineColor(_color);
}

void Brick::draw()
{
	rectangle.draw();
}

void Brick::getPosition(float& _left, float& _right, float& _top, float& _bottom) const
{
	_left = left;
	_right = right;
	_top = top;
	_bottom = bottom;
}

float Brick::getXPosition(float& _left, float& _right) const
{
	_left = left;
	_right = right;
	float xPos = (left+right)/2;
	return xPos;
}

float Brick::getYPosition(float& _top, float& _bottom) const
{
	_top = top;
	_bottom = bottom;
	float yPos = (top+bottom)/2;
	return yPos;
}