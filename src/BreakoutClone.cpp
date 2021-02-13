#include "Paddle.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>


/*Breakout Clone is a student/hobby project created by Mark Tasaka
* that builds on Mr. John Horton's 'Pong" game from his book
* Beginning C++ Game Program (second edition), published by Packt>
*/

using namespace sf;



const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;

int main()
{
	// Create a video mode object
	VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Create and open a window for the game

	//RenderWindow window(vm, "Breakout Clone", Style::Fullscreen);
	RenderWindow window(vm, "Breakout Clone", Style::Close);

	int score = 0;
	int lives = 3;

	// Create a paddle
	Paddle paddle(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 80);

	// We will add a ball in the next chapter
	Ball ball(SCREEN_WIDTH / 2, 0);

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
	hud.setCharacterSize(32);

	// Choose a color
	hud.setFillColor(Color::White);

	hud.setPosition(20, 20);

	// Here is our clock for timing everything
	Clock clock;

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
		ss << "Score:" << score << "\nBalls:" << lives;
		hud.setString(ss.str());


		// Handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			// reverse the ball direction
			ball.reboundBottom();

			// Remove a life
			lives--;

			// Check for zero lives
			if (lives < 1) {
				// reset the score
				score = 0;
				// reset the lives
				lives = 3;
			}

		}

		// Handle ball hitting top
		if (ball.getPosition().top < 0)
		{
			ball.reboundPaddleOrTop();

			// Add a point to the players score
			score++;

		}

		// Handle ball hitting sides
		if (ball.getPosition().left < 200 ||
			ball.getPosition().left + 10 > window.getSize().x)
		{
			ball.reboundSides();
		}

		// Has the ball hit the paddle?
		if (ball.getPosition().intersects(paddle.getPosition()))
		{
			// Hit detected so reverse the ball and score a point
			ball.reboundPaddleOrTop();
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
		window.display();
	}

	return 0;
}

