// Erich Viebrock
//
// COMP53 Fall 2012
//
// Ball.h
//
// Defines Ball objects for the Breakout game.

#ifndef BALL_DOT_H
#define BALL_DOT_H
#include "InterAct2D.h"

class Ball
{
public:
	// Create a  Ball.
	Ball(float _center_x=0.0, float _center_y=0.0,
	 	 float _radius=0.0,
		 float _speed_x=0.0, float _speed_y=0.0,
		 Color _color=black);

	// Destroy a Ball - currently nothing to do
	virtual ~Ball() { }

	// Draw ball at current position.
	virtual void draw();

	// Move ball based on current velocity.
	virtual void move(float elapsed_time_sec);

	// Change ball velocity in response to a collision.
	// Each flag indicates that ball is hitting something, coming from the
	// indicated direction and should bounce back in that direction.
	// For example, (bounce_left==true) means that the ball is hitting something
	// to its right, and should respoind by bouncing back to the left.
	virtual void collision(bool bounce_left, bool bounce_right,
		                   bool bounce_up, bool bounce_down);

	// Change ball horizontal speed directly.
	virtual void addHorizontalSpeed(float _delta_speed);

	// Get current position and radius.
	virtual float getRadius() const;
	virtual Point getPosition() const;

	// Get estimate of next position assuming a 30 msec frame.
	virtual Point nextPosition() const;

	// Identify ball type
	virtual int getName()
	{
		return 1;
	}

protected:
	Oval circle;
	float x_position, y_position, radius;
	float x_velocity, y_velocity;
};

#endif
