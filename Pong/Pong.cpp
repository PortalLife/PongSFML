#include "Pong.h"

void PongGame::resetLevel() {

	// Sets default positions for all elements

	paddle.setPosition(0, 300);
	paddle2.setPosition(992, 300);
	ball.setPosition(512, 384);

	// creates a RNG angle of attack for the ball on the level being reset

	float angle = rand() / 60;
	ballDirection = sf::Vector2f(sin(angle), cos(angle));
	ballVelocity = 450;
}

void PongGame::updateLevel(sf::Time ptpf) {

	// Stops the paddles going out of bounds

	if (paddle.getPosition().y < 0)
	{
		paddle.setPosition(0, 0);
	}

	else if (paddle.getPosition().y > 640)
	{
		paddle.setPosition(0, 640);
	}

	else if (paddle2.getPosition().y < 0)
	{
		paddle2.setPosition(995, 0);
	}

	else if (paddle2.getPosition().y > 640)
	{
		paddle2.setPosition(995, 640);
	}

	// Stops the ball going out of bounds, speeds up for gameplay effect

	if (ball.getPosition().y > 750 || ball.getPosition().y < 0)
	{
		ballDirection.y = -ballDirection.y;
		ballVelocity += 10;
	}

	// Player 1 or Player 2 scores, level is reset

	if (ball.getPosition().x < 0) {
		player1Score++;
		resetLevel();
	}

	else if (ball.getPosition().x > 1024)
	{
		player2Score++;
		resetLevel();
	}

	// Hit collision for the ball and paddles

	sf::FloatRect paddle1Box = paddle.getGlobalBounds();
	sf::FloatRect paddle2Box = paddle2.getGlobalBounds();
	sf::FloatRect ballBox = ball.getGlobalBounds();

	if (paddle1Box.intersects(ballBox) || paddle2Box.intersects(ballBox)) {

		ballDirection.x =-ballDirection.x;
		
        ballVelocity += 10; 
	}

	// Ball moves in a specified direction, controlled by frame rate.

	ball.move(ballDirection * ptpf.asSeconds() * ballVelocity);
}