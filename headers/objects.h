#include <SFML/Graphics.hpp>
#include <vector>

class Ball {
private:
	sf::CircleShape ball;
	float ballMoveDirectionY;
	float ballMoveDirectionX;
	float ballSpeedMultiplier;
public:
	Ball() : ball(10.f) { 
		this->ballMoveDirectionY = 3.f;
		this->ballMoveDirectionX = 0.f;
		this->ballSpeedMultiplier = 1;
	}
};