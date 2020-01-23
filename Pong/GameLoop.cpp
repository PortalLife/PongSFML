#include "Pong.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <sstream>
#include "Constants.h"

PongGame::PongGame(){}

PongGame::~PongGame() {}

// Game loop functions

void PongGame::initialise()
{

	// Sets the default settings of the game and initialises the random seed to be used in UpdateLevel();

	wndw.create(sf::VideoMode(APPHEIGHT,APPWIDTH), APPNAME);

	player1Score = 0;
	player2Score = 0;

	paddle.scale(0.5f, 0.5f);
	paddle2.scale(0.5f, 0.5f);
	ball.scale(0.5f, 0.5f);

	srand(time((NULL)));
}

void PongGame::loadContent()
{
	// This needs to be improved, less copy and paste.

	textures[0].loadFromFile("Textures/bg_1.jpg");
	textures[1].loadFromFile("Textures/ball.jpg");
	textures[2].loadFromFile("Textures/paddle.png");

	bg.setTexture(textures[0]);
	ball.setTexture(textures[1]);
	
	paddle.setTexture(textures[2]);
	paddle2.setTexture(textures[2]);

	font.loadFromFile("Fonts/Verdana.ttf");

	for (int i = 0; i <= PongGame::Time; i++)
	{
		text[i].setFont(font);
		text[i].setFillColor(sf::Color::White);
		text[i].setCharacterSize(26);
	}

	text[Score].setString("Player 1: ");
	text[Score].setPosition(100, 50);
	
	text[Score2].setString("Player 2: ");
	text[Score2].setPosition(800, 50);
	
	text[Time].setString("Time: ");
	text[Time].setPosition(500, 50);

	// Sets default position

	resetLevel();
}


void PongGame::update(sf::Time ptpf)
{
	static sf::Time  gameClock; // Game clock has to be static or will not count time properly.
	gameClock += ptpf;

	std::ostringstream seconds;
	seconds << std::fixed;

	seconds.precision(0);
	seconds << gameClock.asSeconds();

	text[Score].setString("Player 1: " + std::to_string(player1Score));
	text[Score2].setString("Player 2: " + std::to_string(player2Score));
	
	text[Time].setString("Time : " + seconds.str());
	text[Time].setPosition(500, 50);

   updateLevel(ptpf);
}

void PongGame::handleEvents()
{
	sf::Event event;


	while (wndw.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handleInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handleInput(event.key.code, false);
			break;
		
		case sf::Event::Closed:
			wndw.close();
			break;
		}
	}
}

void PongGame::handleInput(sf::Keyboard::Key pkey, bool ppressed) 
{
	if (pkey == sf::Keyboard::Key::W)
	{
		paddle.move(0, -25);
	}

	if (pkey == sf::Keyboard::Key::Up)
	{
		paddle2.move(0, -25);
	}

	if (pkey == sf::Keyboard::Key::S)
	{
		paddle.move(0, 25);
	}

	if (pkey == sf::Keyboard::Key::Down)
	{
		paddle2.move(0, 25);
	}
}

void PongGame::render()
{

	wndw.clear();

	wndw.draw(bg);
	wndw.draw(paddle);
	wndw.draw(paddle2);
	wndw.draw(ball);

	for (int i = 0; i <= PongGame::Time; i++)
	{
		wndw.draw(text[i]);
	}

	wndw.display();
}

void PongGame::cleanup() {

	// No dynamic objects to clean
}

void PongGame::runGame() {

	//Initialise the Game Window
	
	initialise();
	loadContent();

	sf::Clock tclock;
	sf::Time tprevtime = tclock.restart();

	//While the window is open run the game loop.

	while (wndw.isOpen())
	{
		tpf = tclock.getElapsedTime() - tprevtime;
		t_update = tclock.getElapsedTime() - tprevtime;
		tprevtime = tclock.getElapsedTime();

		handleEvents();
		update(t_update);
		render();
	}
	cleanup();
}

