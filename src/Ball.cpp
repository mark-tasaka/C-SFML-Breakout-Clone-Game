#include "Ball.h"

/*Breakout Clone is a student/hobby project created by Mark Tasaka
* that builds on Mr. John Horton's 'Pong" game from his book
* Beginning C++ Game Program (second edition), published by Packt>
*/


Ball::Ball(double rad, float startX, float startY, Color colour): m_Shape(rad)
{
	m_Position.x = startX;
	m_Position.y = startY;
	m_Shape.setFillColor(colour);
	m_Shape.setPosition(m_Position);
}

FloatRect Ball::getPosition()
{
	return m_Shape.getGlobalBounds();
}

CircleShape Ball::getShape()
{
	return m_Shape;
}


float Ball::getXVelocity()
{
	return m_DirectionX;
}

void Ball::reboundSides()
{
	m_DirectionX = -m_DirectionX;
}

void Ball::reboundPaddleOrTop()
{
	m_DirectionY = -m_DirectionY;

}

void Ball::reboundBottom()
{
	m_Position.y = 0;
	m_Position.x = 500;
	m_DirectionY = -m_DirectionY;
}

void Ball::ballReSpawn()
{
	m_Position.y = 200;
	m_Position.x = 500;

}

void Ball::reboundBrick()
{
	m_DirectionX = -m_DirectionX;
	m_DirectionY = -m_DirectionY;
}

void Ball::update(Time dt)
{
	// Update the ball position variables
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

	// Move the ball and the bat
	m_Shape.setPosition(m_Position);
}


//D'tor
Ball::~Ball()
{
}
