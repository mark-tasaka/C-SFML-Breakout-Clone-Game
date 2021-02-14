#pragma once
#ifndef BRICK_H
#define BRICK_H
/*Breakout Clone is a student/hobby project created by Mark Tasaka
* that builds on Mr. John Horton's 'Pong" game from his book
* Beginning C++ Game Program (second edition), published by Packt>
*/

#include <SFML/Graphics.hpp>
#include "stdafx.h"

using namespace sf;

class Brick
{
private:
	Vector2f m_Position;

	// A RectangleShape object
	RectangleShape m_Shape;

public:
	Brick(Vector2f size, Vector2f position, Color colour);
	bool m_IsAlive = true;
	void setSize(Vector2f size);
	RectangleShape getShape();
	Vector2f topRight();
	Vector2f topLeft();
	Vector2f bottomRight();
	Vector2f bottomLeft();
	void destroyBrick();
	~Brick();

};


#endif
