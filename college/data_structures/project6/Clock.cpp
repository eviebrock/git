// COMP53 Fall 2012
//
// Clock.cpp
//
// Implements Clock objects for the Breakout game.

#include "Clock.h"
const float CLOCK_WIDTH = 200.0;
const float CLOCK_HEIGHT = 20.0;

Clock::Clock(float _left_x, float _top_y, float _time,
			 Color _fg_color, Color _bg_color)
:	text(Point(_left_x+CLOCK_WIDTH/2.0f, _top_y+CLOCK_HEIGHT/2.0f), string("00.00")),
	background(Point(_left_x+CLOCK_WIDTH/2.0f, _top_y+CLOCK_HEIGHT/2.0f), CLOCK_WIDTH, CLOCK_HEIGHT),
	left(_left_x), top(_top_y), 
	time(_time)
{ 
	text.setFillColor(_fg_color);
	text.setOutlineColor(_fg_color);
	background.setFillColor(_bg_color);
	background.setOutlineColor(_bg_color);
	setDisplay();
}

void Clock::draw()
{
	background.draw();
	text.draw();
}

void Clock::setDisplay()
{
	// limit time between 0 and 99 minutes
	if (time > 5940.0) time = 5940.0;
	if (time < 0.0) time = 0.0;

	char s[20];
	float temp = time;

	int minutes = int(time)/60;
	temp -= minutes*60;
	int m1 = minutes/10;
	int m2 = minutes%10;

	int seconds = int(temp);
	temp -= seconds;
	int s1 = seconds/10;
	int s2 = seconds%10;

	int hundreths = int(temp*100);
	int h1 = hundreths/10;
	int h2 = hundreths%10;

	s[0] = m1 + '0';
	s[1] = m2 + '0';
	s[2] = ':';
	s[3] = s1 + '0';
	s[4] = s2 + '0';
	s[5] = '.';
	s[6] = h1 + '0';
	s[7] = h2 + '0';
	s[8] = '\0';

	text.setText(string(s));
}
