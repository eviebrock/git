// Erich Viebrock
//
// COMP53 Fall 2012
//
// Clock.cpp
//
// Implements Clock objects for the Breakout game.

#include "ScoreBoard.h"
const float SCOREBOARD_WIDTH = 200.0;
const float SCOREBOARD_HEIGHT = 20.0;

ScoreBoard::ScoreBoard(float _left_x, float _top_y, float _time,
			 Color _fg_color, Color _bg_color)
:	text(Point(_left_x+SCOREBOARD_WIDTH/2.0f, _top_y+SCOREBOARD_HEIGHT/2.0f), string("Score: 0")),
	background(Point(_left_x+SCOREBOARD_WIDTH/2.0f, _top_y+SCOREBOARD_HEIGHT/2.0f), SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT),
	left(_left_x), top(_top_y), 
	time(_time)
{ 
	text.setFillColor(_fg_color);
	text.setOutlineColor(_fg_color);
	background.setFillColor(_bg_color);
	background.setOutlineColor(_bg_color);
	hitBrick2 = 0;
	hitBrick1 = -1;
	updateScore();
}

void ScoreBoard::draw()
{
	background.draw();
	text.draw();
}

void ScoreBoard::updateScore()
{
	if (hitBrick1 < 9 && hitBrick2 == 0)
	{
		hitBrick1++;
		char score[10];
		score[0] = 'S';
		score[1] = 'c';
		score[2] = 'o';
		score[3] = 'r';
		score[4] = 'e';
		score[5] = ':';
		score[6] = ' ';
		score[7] = ' ';
		score[8] = hitBrick1 + '0';
		score[9] = '\0';
		text.setText(string(score));
	}
	else if (hitBrick1 == 9)
	{
		hitBrick2++;
		hitBrick1 = 0;
		char score[10];
		score[0] = 'S';
		score[1] = 'c';
		score[2] = 'o';
		score[3] = 'r';
		score[4] = 'e';
		score[5] = ':';
		score[6] = ' ';
		score[7] = hitBrick2 + '0';
		score[8] = hitBrick1 + '0';
		score[9] = '\0';
		text.setText(string(score));
	}
	else
	{
		hitBrick1++;
		char score[10];
		score[0] = 'S';
		score[1] = 'c';
		score[2] = 'o';
		score[3] = 'r';
		score[4] = 'e';
		score[5] = ':';
		score[6] = ' ';
		score[7] = hitBrick2 + '0';
		score[8] = hitBrick1 + '0';
		score[9] = '\0';
		text.setText(string(score));
	}
}