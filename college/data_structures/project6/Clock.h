// COMP53 Fall 2012
//
// Clock.h
//
// Defines Clock objects for the Breakout game.

#ifndef CLOCK_DOT_H
#define CLOCK_DOT_H
#include "InterAct2D.h"

class Clock
{
public:
	Clock(float _left_x=0.0, float _top_y=0.0, float _time=0.0,
		  Color _fg_color=white, Color _bg_color=black);
	void draw();
	void changeBy(float _delta_time) 
	{
		time += _delta_time;
		setDisplay();
	}
	void changeTo(float _new_time)
	{
		time = _new_time;
		setDisplay();
	}

private:
	Text text;
	Rect background;
	float left, top;
	float time;
	void setDisplay();
};

#endif