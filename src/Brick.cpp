/*Breakout Clone is a student/hobby project created by Mark Tasaka
* that builds on Mr. John Horton's 'Pong" game from his book
* Beginning C++ Game Program (second edition), published by Packt>
*/

#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include "Brick.h"

using namespace sf;

Brick::Brick(Vector2f size, Vector2f position, Color colour): m_IsAlive(true)
{
	m_Shape.setSize(size);
	m_Shape.setPosition(position);
	m_Shape.setFillColor(colour);
	m_Shape.setOutlineColor(Color::White);
	m_Shape.setOutlineThickness(-1);
}

void Brick::setSize(Vector2f size)
{
	size = Vector2f(100, 20);
	m_Shape.setSize(size);
}

RectangleShape Brick::getShape()
{
	return m_Shape;
}


Vector2f Brick::topRight()
{
	return Vector2f(m_Shape.getPosition().x + m_Shape.getSize().x,
		m_Shape.getPosition().y);
}

Vector2f Brick::topLeft()
{
	return m_Shape.getPosition();
}

Vector2f Brick::bottomRight()
{
	return Vector2f(m_Shape.getPosition().x + m_Shape.getSize().x,
		m_Shape.getPosition().y + m_Shape.getSize().y);
}

Vector2f Brick::bottomLeft()
{
	return Vector2f(m_Shape.getPosition().x,
		m_Shape.getPosition().y + m_Shape.getSize().y);
}

void Brick::destroyBrick()
{
	m_Shape.setPosition(90000, 90000);
	m_IsAlive = false;
}

Brick::~Brick()
{

}