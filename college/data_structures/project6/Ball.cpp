// COMP53 Fall 2012
//
// Ball.cpp
//
// Implements Ball objects for the Breakout game.

#include "Ball.h"

Ball::Ball(float _center_x, float _center_y, float _radius,
		   float _speed_x, float _speed_y,
		   Color _color)
:	circle(Point(_center_x, _center_y), _radius,  _radius),
	x_position(_center_x), y_position(_center_y), radius(_radius),
	x_velocity(_speed_x), y_velocity(_speed_y)
{ 
	circle.setFillColor(_color);
	circle.setOutlineColor(_color);
}

void Ball::draw()
{
	circle.draw();
}

void Ball::move(float elapsed_time_sec)
{
	x_position += x_velocity*elapsed_time_sec;
	y_position += y_velocity*elapsed_time_sec;
	circle.moveTo(Point(x_position, y_position));
}

void Ball::collision(bool bounce_left, bool bounce_right, 
               bool bounce_up, bool bounce_down)
{
	if (bounce_left  && (x_velocity > 0.0)) x_velocity *= -1.0;
	if (bounce_right && (x_velocity < 0.0)) x_velocity *= -1.0;
	if (bounce_up    && (y_velocity > 0.0)) y_velocity *= -1.0;
	if (bounce_down  && (y_velocity < 0.0)) y_velocity *= -1.0;
}

float Ball::getRadius() const
{ 
	return radius; 
} 

Point Ball::getPosition() const
{
	Point p(x_position, y_position);
	return p;
}

Point Ball::nextPosition() const
{
	Point p(x_position+x_velocity*0.03f, y_position+y_velocity*0.03f);
	return p;
}

void Ball::addHorizontalSpeed(float _delta_speed)
{
	x_velocity += _delta_speed;
}
