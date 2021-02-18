#pragma once
#ifndef BALL_H
#define BALL_H
/*Breakout Clone is a student/hobby project created by Mark Tasaka
* that builds on Mr. John Horton's 'Pong" game from his book
* Beginning C++ Game Program (second edition), published by Packt>
*/

#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "Constant.h"
#include "Brick.h"

using namespace sf;

class Ball
{
private:
	Vector2f m_Position;	
	CircleShape m_Shape;

	//float m_Speed = BALL_SPEED_BASE;
	float m_DirectionX = 0.2f;
	float m_DirectionY = 0.2f;

public:
	Ball(double rad, float startX, float startY, Color colour);

	FloatRect getPosition();

	CircleShape getShape();

	float getXVelocity();

	float m_Speed = BALL_SPEED_BASE;

	void reboundSides();

	void reboundPaddleOrTop();

	void reboundBottom();

	void reboundBrick();

	void ballReSpawn();

	void update(Time dt);

	~Ball();

};

#endif // BALL_H
