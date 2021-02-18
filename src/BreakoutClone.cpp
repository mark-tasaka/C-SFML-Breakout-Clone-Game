/*Breakout Clone is a student/hobby project created by Mark Tasaka
* that builds on Mr. John Horton's 'Pong" game from his book
* Beginning C++ Game Program (second edition), published by Packt>
*/
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "Brick.cpp"
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Constant.h"

using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);

	//enum for the 5 states of the game:
	enum class State { START, PLAY, PAUSE, NEXT_LEVEL, GAME_OVER };

	//Start State of the Game
	State state = State::START;

	// Create and open a window for the game
	RenderWindow window(vm, "Breakout Clone", Style::Close);

	unsigned int level = 1;
	unsigned int score = 0;
	unsigned int hiScore = 0;
	unsigned int lives = BALLS;

	// Create a paddle
	Paddle paddle(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30);

	//Ball Object
	Ball ball(6, SCREEN_WIDTH / 2, 200, BALL_COLOUR);

	float levelConversion = (float)level;

	ball.m_Speed += (BALL_SPEED_LEVEL * levelConversion);

	unsigned int Test = 3;

	//unsigned int bricksRemaining = BRICKS_START - 1;

	unsigned int bricksRemaining = Test - 1;

	vector <Brick> bricks;
	float startX = 250.0f;
	float startY = 50.0f;

	Color brickColour = BRICK_COLOURS[0];

	for (int i = 1; i < Test; i++)
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


	// The Start State
	Texture startGamePage;
	startGamePage.loadFromFile("graphic/start.png");
	Sprite spriteStartGame;
	spriteStartGame.setTexture(startGamePage);

	//Game Play State
	Texture background;
	background.loadFromFile("graphic/background.png"); 
	Sprite spriteBackground;
	spriteBackground.setTexture(background);

	// The Pause State
	Texture pauseGamePage;
	pauseGamePage.loadFromFile("graphic/paused.png");
	Sprite spritePauseGame;
	spritePauseGame.setTexture(pauseGamePage);

	// The Game Over State
	Texture gameOverPage;
	gameOverPage.loadFromFile("graphic/gameOver.png");
	Sprite spriteGameOver;
	spriteGameOver.setTexture(gameOverPage);


	// The Level Up State
	Texture levelUpPage;
	levelUpPage.loadFromFile("graphic/nextLevel.png");
	Sprite spriteLevelUp;
	spriteLevelUp.setTexture(levelUpPage);

	// Create a Text object called HUD
	Text hud;

	// A cool retro-style font
	Font font;
	font.loadFromFile("font/PixelDigivolve.otf");

	// Set the font to our retro-style
	hud.setFont(font);

	// Make it nice and big
	hud.setCharacterSize(24);

	// Choose a color
	hud.setFillColor(Color::White);

	hud.setPosition(20, 20);

	// Load the high score from a text file/
	std::ifstream inputFile("topScore/highScore.txt");
	if (inputFile.is_open())
	{
		inputFile >> hiScore;
		inputFile.close();
	}

	
	// Hi Displayed On Start and Level Up Pages
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(24);
	hiScoreText.setFillColor(Color::Yellow);
	hiScoreText.setPosition(500, 450);
	std::stringstream ts;
	ts << "Higest Score: " << hiScore;
	hiScoreText.setString(ts.str());

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
			{
				// Quit the game when the window is closed
				window.close();
			}

			if (event.key.code == Keyboard::Return && state == State::START)
			{
				state = State::PLAY;
			}


			if (event.key.code == Keyboard::Return && state == State::NEXT_LEVEL)
			{
				state = State::PLAY;
			}

			//return from paused game
			if (event.key.code == Keyboard::Return &&
				state == State::PAUSE)
			{
				state = State::PLAY;
				// Reset the clock so there isn't a frame jump
				clock.restart();
			}

			//new Game from Game Over Stage
			if (event.key.code == Keyboard::Return &&
				state == State::GAME_OVER)
			{
				// Reset the clock so there isn't a frame jump
				score = 0;
				level = 1;
				clock.restart();

				state = State::PLAY;
			}


		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (state == State::PLAY)
		{


			// Pause a game while playing
			if (event.key.code == Keyboard::Space &&
				state == State::PLAY)
			{
				state = State::PAUSE;
			}


			// Handle the pressing and releasing of the arrow keys
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				if (paddle.getPosition().left < 200)
				{
					paddle.stopLeft();
				}
				else
				{
					paddle.moveLeft();
				}
			}
			else
			{
				paddle.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{

				if (paddle.getPosition().left + 110 > window.getSize().x )
				{
					paddle.stopRight();
				}
				else
				{
					paddle.moveRight();
				}
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
			ss << "Level: " << level << "\n\nScore:\n" << score << "\n\nBalls: " << lives << "\n\nBricks\nRemaining:\n" << bricksRemaining << "\n\nTop Score:\n" << hiScore;
			hud.setString(ss.str());

			//Ball hitting brick
			for (int i = 0; i < bricks.size(); i++)
			{
				//if(ball. >= bricks[i].bottomLeft() )
				if (ball.getPosition().intersects(bricks[i].getShape().getGlobalBounds()))
				{
					bricks[i].m_IsAlive = false;
					bricks[i].destroyBrick();
					hit.play();
					score += 10;
					bricksRemaining -= 1;
					ball.reboundBrick();

					if (score > hiScore)
					{
						hiScore = score;
					}

					if (bricksRemaining == 0)
					{
						state = State::NEXT_LEVEL;
						level += 1;

						//RESET THE LEVEL HERE
						std::string levelString = to_string(level);
						//std::vector<Brick> a = Brick::spawnBricks();

					}

				}
			}


			// Handle ball hitting the bottom
			if (ball.getPosition().top > window.getSize().y)
			{
				// reverse the ball direction
				ball.ballReSpawn();

				miss.play();

				// Remove a life
				lives--;

				// Check for zero lives
				if (lives < 1) {

					state = State::GAME_OVER;

					std::ofstream outputFile("topScore/highScore.txt");
					outputFile << hiScore;
					outputFile.close();


					// reset the lives
					lives = BALLS;
				}

			}

			// Handle ball hitting top
			if (ball.getPosition().top < 0)
			{
				ball.reboundPaddleOrTop();

				hit.play();


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
		}
		/*
		Draw the paddle, the ball and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/
		window.clear();

		if (state == State::START)
		{
			window.draw(spriteStartGame);
			window.draw(hiScoreText);
		}

		if (state == State::PLAY)
		{
			window.draw(spriteBackground);
			window.draw(hud);
			window.draw(paddle.getShape());
			window.draw(ball.getShape());

			for (auto& theBrick : bricks)
			{
				window.draw(theBrick.getShape());
			}

		}


		if (state == State::PAUSE)
		{

			window.draw(spriteBackground);
			window.draw(hud);
			window.draw(paddle.getShape());
			window.draw(ball.getShape());

			for (auto& theBrick : bricks)
			{
				window.draw(theBrick.getShape());
			}

			window.draw(spritePauseGame);
		}



		if (state == State::GAME_OVER)
		{

			window.draw(spriteBackground);
			window.draw(hud);
			window.draw(paddle.getShape());
			window.draw(ball.getShape());

			for (auto& theBrick : bricks)
			{
				window.draw(theBrick.getShape());
			}

			window.draw(spriteGameOver);
		}


		if (state == State::NEXT_LEVEL)
		{

			window.draw(spriteBackground);
			window.draw(hud);
			window.draw(paddle.getShape());
			window.draw(ball.getShape());

			for (auto& theBrick : bricks)
			{
				window.draw(theBrick.getShape());
			}

			window.draw(spriteLevelUp);
		}


		window.display();
	}

	return 0;
}

