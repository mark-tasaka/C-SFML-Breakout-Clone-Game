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