#pragma once

#include <SFML/Graphics.hpp>

class PongGame
{

public:

	PongGame();
	~PongGame();
	void runGame(); // Runs the game loop

private:

	//	--Function definitions -- 			

	// Defining game loop functions

	void    initialise();			
	void    loadContent();   

	void	handleEvents();        
	void	update(sf::Time ptpf);

	void	render();				
	void    cleanup();				

	void	handleInput(sf::Keyboard::Key pkey, bool ppressed);  
	
	void    resetLevel();  // Gameplay function when a player scores
	void    updateLevel(sf::Time ptpf);
						
	// --Variable definitions--

	// Enumeration representing display text items

	enum HUD {Score, Score2, Time};

	sf::RenderWindow wndw; 

	sf::Font font; 

	sf::Texture textures[3];  // Stores all textures
	sf::Text text[3];

	sf::Sprite ball;
	sf::Sprite bg;
	sf::Sprite paddle, paddle2;

	sf::Time  tpf;      // Time per frame
	sf::Time  t_update;	//Time object storing the current update time
	
	// Game logic variables

	unsigned int player1Score, player2Score;
	sf::Vector2f ballDirection;
	float ballVelocity;
};