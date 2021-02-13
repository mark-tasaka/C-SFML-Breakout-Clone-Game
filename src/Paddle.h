#pragma once
#include <SFML/Graphics.hpp>


/*Breakout Clone is a student/hobby project created by Mark Tasaka
* that builds on Mr. John Horton's 'Pong" game from his book
* Beginning C++ Game Program (second edition), published by Packt>
*/

using namespace sf;

class Paddle
{
private:
	Vector2f m_Position;

	// A RectangleShape object
	RectangleShape m_Shape;

	float m_Speed = 1000.0f;

	bool m_MovingRight = false;
	bool m_MovingLeft = false;


public:
	Paddle(float startX, float startY);

	FloatRect getPosition();

	RectangleShape getShape();

	void moveLeft();

	void moveRight();

	void stopLeft();

	void stopRight();

	void update(Time dt);

};
