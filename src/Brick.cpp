/*Breakout Clone is a student/hobby project created by Mark Tasaka
* that builds on Mr. John Horton's 'Pong" game from his book
* Beginning C++ Game Program (second edition), published by Packt>
*/

#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "Brick.h"
#include "Constant.h"

using namespace sf;

Brick::Brick(Vector2f size, Vector2f position, Color colour): m_IsAlive(true)
{
	m_BrickShape.setSize(size);
	m_BrickShape.setPosition(position);
	m_BrickShape.setFillColor(colour);
	m_BrickShape.setOutlineColor(Color::White);
	m_BrickShape.setOutlineThickness(-1);
}

void Brick::setSize(Vector2f size)
{
	size = Vector2f(BRICK_WIDTH, BRICK_HEIGHT);
	m_BrickShape.setSize(size);
}

std::vector<Brick> Brick::spawnBricks()
{
	vector <Brick> bricks;
	float startX = 250.0f;
	float startY = 50.0f;

	Color brickColour = BRICK_COLOURS[0];

	for (int i = 1; i < BRICKS_START; i++)
	{

		Vector2f brickPos = Vector2f(startX, startY);
		Brick brick(BRICK_SIZE, brickPos, brickColour);
		bricks.push_back(brick);
		startX += 100.0f;

		if (i % 9 == 0)
		{
			startY += 20.0f;
			startX = 250.0f;
		}

		if (i >= 9 && i <= 17 || i >= 45 && i <= 53)
		{
			brickColour = BRICK_COLOURS[1];
		}

		if (i >= 18 && i <= 26 || i >= 54 && i <= 64)
		{
			brickColour = BRICK_COLOURS[2];
		}

		if (i >= 27 && i <= 35)
		{
			brickColour = BRICK_COLOURS[3];
		}

		if (i >= 36 && i <= 44)
		{
			brickColour = BRICK_COLOURS[0];
		}
	}

	return bricks;

}

RectangleShape Brick::getShape()
{
	return m_BrickShape;
}


Vector2f Brick::topRight()
{
	return Vector2f(m_BrickShape.getPosition().x + m_BrickShape.getSize().x,
		m_BrickShape.getPosition().y);
}

Vector2f Brick::topLeft()
{
	return m_BrickShape.getPosition();
}

Vector2f Brick::bottomRight()
{
	return Vector2f(m_BrickShape.getPosition().x + m_BrickShape.getSize().x,
		m_BrickShape.getPosition().y + m_BrickShape.getSize().y);
}

Vector2f Brick::bottomLeft()
{
	return Vector2f(m_BrickShape.getPosition().x,
		m_BrickShape.getPosition().y + m_BrickShape.getSize().y);
}

void Brick::destroyBrick()
{
	m_BrickShape.setPosition(90000, 90000);
	m_IsAlive = false;
}

Brick::~Brick()
{

}