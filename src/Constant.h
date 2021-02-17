#pragma once
#ifndef CONSTANT_H	
#define CONSTANT_H

/*Breakout Clone is a student/hobby project created by Mark Tasaka
* that builds on Mr. John Horton's 'Pong" game from his book
* Beginning C++ Game Program (second edition), published by Packt>
*/

using namespace sf;
using namespace std;

const unsigned int SCREEN_WIDTH = 1200;
const unsigned int SCREEN_HEIGHT = 900;
const unsigned int BALLS = 2;
const unsigned int BRICK_WIDTH = 100;
const unsigned int BRICK_HEIGHT = 20;
const float BALL_SPEED_BASE = 500.0f;
const float BALL_SPEED_LEVEL = 500.0f;
const unsigned int BRICKS_START = 64;

const Vector2f BRICK_SIZE = Vector2f(100, 20);
//const Color BRICK_COLOUR = Color::Cyan;

const vector<Color> BRICK_COLOURS = { Color::Cyan, Color::Blue, Color::Magenta, Color::Green };
const Color BALL_COLOUR = Color::Green;
//const unsigned int FPS = 60;
//const unsigned int FRAME_TARGET_TIME = 1000 / FPS;


#endif
