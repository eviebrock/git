// COMP53 Fall 2012
//
// Paddle.cpp
//
// Implements Paddle objects for the Breakout game.

#include "Paddle.h"

// motion parameters
static const float MAX_SPEED = 500.0;
static const float THRUSTER_ACCELERATION = 40.0;
static const float FRICTION_ACCELERATION = 5.0;

Paddle::Paddle(float _center_x, float _center_y, float _width, float _height,
			 Color _color)
:	rectangle(Point(_center_x, _center_y), _width, _height),
	left(_center_x - _width/2.0f), right(_center_x + _width/2.0f), 
	top(_center_y - _height/2.0f), bottom(_center_y + _height/2.0f),
	width(_width), velocity(0.0f)
{
	rectangle.setFillColor(_color);
	rectangle.setOutlineColor(_color);
}

void Paddle::draw()
{
	rectangle.draw();
}

void Paddle::move(float _delta_time_sec, float _range_top, float _range_bottom)
{
	// move the paddle and ensure it stays in screen
	top += velocity*_delta_time_sec;
	if (top < _range_top) top = _range_top;
	if ((top+width) > _range_bottom) top = _range_bottom - width;
	bottom = top + width; 
	rectangle.moveTo(Point((top+right)/2, (top+bottom)/2));

	// friction
	if (abs(velocity) < FRICTION_ACCELERATION) velocity = 0.0;
	else if (velocity < 0.0) velocity += FRICTION_ACCELERATION;
	else if (velocity > 0.0) velocity -= FRICTION_ACCELERATION;
}

void Paddle::leftThrust()
{
	// apply thrust
	//if (velocity >= -FRICTION_ACCELERATION) velocity -= THRUSTER_ACCELERATION*5.0f;
	//else 
	velocity -= THRUSTER_ACCELERATION;
	// regulate speed
	if (velocity < -MAX_SPEED) velocity = -MAX_SPEED;
}

void Paddle::rightThrust()
{
	// apply thrust
	//if (velocity <= FRICTION_ACCELERATION) velocity += THRUSTER_ACCELERATION*5.0f;
	//else 
	velocity += THRUSTER_ACCELERATION;
	// regulate speed
	if (velocity > MAX_SPEED) velocity = MAX_SPEED;
}

float Paddle::getSpeed() const 
{ 
	return velocity; 
}

void Paddle::getPosition(float& _left, float& _right, float& _top, float& _bottom) const
{
	_left = left;
	_right = right;
	_top = top;
	_bottom = bottom;
}