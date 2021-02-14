/*Breakout Clone is a student/hobby project created by Mark Tasaka
* that builds on Mr. John Horton's 'Pong" game from his book
* Beginning C++ Game Program (second edition), published by Packt>
*/
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "stdafx.h"
#include <iostream>

using namespace sf;
using namespace std;


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;
const int BALLS = 5;
const Vector2f BRICK_SIZE = Vector2f(100, 20);
const Color BALL_COLOUR = Color::Green;
const Color BRICK_COLOUR = Color::Cyan;

int main()
{
	// Create a video mode object
	VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Create and open a window for the game

	//RenderWindow window(vm, "Breakout Clone", Style::Fullscreen);
	RenderWindow window(vm, "Breakout Clone", Style::Close);

	int level = 1;
	int score = 0;
	int lives = BALLS;

	// Create a paddle
	Paddle paddle(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 80);

	//Ball Object
	//Ball ball(SCREEN_WIDTH / 2, 0);
	Ball ball(6, SCREEN_WIDTH / 2, 0, BALL_COLOUR);

	vector <Brick> bricks;
	float startX = 250;
	float startY = 100;


	for (int i = 0; i < 30; i++)
	{
		Vector2f brickPos = Vector2f(startX, startY);
		Brick brick(BRICK_SIZE, brickPos, BRICK_COLOUR);
		bricks.push_back(brick);
		startX += 100;

		if (i == 8 || i == 17 || i == 26)
		{
			startY += 20;
			startX = 250;
		}
	}

	Texture background;
	background.loadFromFile("graphic/background.png"); 
	Sprite spriteBackground;
	spriteBackground.setTexture(background);

	// Create a Text object called HUD
	Text hud;

	// A cool retro-style font
	Font font;
	font.loadFromFile("font/PixelSplitter-Bold.ttf");

	// Set the font to our retro-style
	hud.setFont(font);

	// Make it nice and big
	hud.setCharacterSize(28);

	// Choose a color
	hud.setFillColor(Color::White);

	hud.setPosition(20, 20);

	// Here is our clock for timing everything
	Clock clock;

	//hit sound
	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sound/hit.wav");
	Sound hit;
	hit.setBuffer(hitBuffer);

	//hit paddle
	SoundBuffer hitBufferPaddle;
	hitBufferPaddle.loadFromFile("sound/hitPaddle.wav");
	Sound hit2;
	hit2.setBuffer(hitBufferPaddle);

	//Miss sound
	SoundBuffer missBuffer;
	missBuffer.loadFromFile("sound/miss.wav");
	Sound miss;
	miss.setBuffer(missBuffer);

	while (window.isOpen())
	{
		/*
		Handle the player input
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Quit the game when the window is closed
				window.close();

		}

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle the pressing and releasing of the arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			paddle.moveLeft();
		}
		else
		{
			paddle.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			paddle.moveRight();
		}
		else
		{
			paddle.stopRight();
		}

		/*
		Update the paddle, the ball and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/
		// Update the delta time
		Time dt = clock.restart();
		paddle.update(dt);
		ball.update(dt);
		// Update the HUD text
		std::stringstream ss;
		ss << "Level:" << level << "\nScore:" << score << "\nBalls:" << lives;
		hud.setString(ss.str());


		// Handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			// reverse the ball direction
			ball.reboundBottom();

			miss.play();

			// Remove a life
			lives--;

			// Check for zero lives
			if (lives < 1) {
				// reset the score
				score = 0;
				// reset the lives
				lives = BALLS;
			}

		}

		// Handle ball hitting top
		if (ball.getPosition().top < 0)
		{
			ball.reboundPaddleOrTop();

			hit.play();

			// Add a point to the players score
			score++;

		}

		// Handle ball hitting sides
		if (ball.getPosition().left < 200 ||
			ball.getPosition().left + 10 > window.getSize().x)
		{
			ball.reboundSides();
			hit.play();
		}

		// Has the ball hit the paddle?
		if (ball.getPosition().intersects(paddle.getPosition()))
		{
			// Hit detected so reverse the ball and score a point
			ball.reboundPaddleOrTop();
			hit2.play();
		}
		/*
		Draw the paddle, the ball and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/
		window.clear();
		window.draw(spriteBackground);
		window.draw(hud);
		window.draw(paddle.getShape());
		window.draw(ball.getShape());

		for (auto& theBrick : bricks)
		{
			window.draw(theBrick.getShape());
		}

		window.display();
	}

	return 0;
}

