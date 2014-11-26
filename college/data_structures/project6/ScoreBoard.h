// Erich Viebrock
//
// COMP53 Fall 2012
//
// Scoreboard.h
//
// Defines Clock objects for the Breakout game.

#ifndef SCOREBOARD_DOT_H
#define SCOREBOARD_DOT_H
#include "InterAct2D.h"

class ScoreBoard
{
public:
	ScoreBoard(float _left_x=0.0, float _top_y=0.0, float _time=456,
		  Color _fg_color=white, Color _bg_color=black);
	void draw();
	void updateScore();

private:
	Text text;
	Rect background;
	float left, top;
	float time;
	void setDisplay();
	int hitBrick2;
	int hitBrick1;
};

#endif