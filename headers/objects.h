#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

std::vector<sf::RectangleShape> generateBricks();

class Ball {
private:
	sf::CircleShape ball;
	float moveDirectionY;
	float moveDirectionX;
	float speedMultiplier;
public:
	Ball() : ball(10.f) {
		this->moveDirectionY = 3.f;
		this->moveDirectionX = 0.f;
		this->speedMultiplier = 1;
	}

	sf::CircleShape getBall()
	{
		return ball;
	}

	float getMoveDirectionX()
	{
		return this->moveDirectionX;
	}

	float getMoveDirectionY()
	{
		return this->moveDirectionY;
	}

	float getSpeedMultiplier()
	{
		return this->speedMultiplier;
	}

	void baseMove();

	void setStartPosition(const sf::RenderWindow& window);

	void collisionCheck(sf::RenderWindow* window, sf::RectangleShape* platform, std::vector<sf::RectangleShape>& bricks, float* platformSpeedMultiplier);
};

class Upgrade {
private:
	sf::RectangleShape upgradeBody;
	std::string upgradeType;
	int active = 0;
public:
	Upgrade() : upgradeBody(sf::Vector2f({ 20.f, 10.f })) {}

	sf::RectangleShape getUpgrade()
	{
		return this->upgradeBody;
	}

	std::string getUpgradeType()
	{
		return this->upgradeType;
	}

	void setActive(const int activeCode)
	{
		this->active = activeCode;
	}

	void baseMove();

	void setBasePosition(float posX, float posY);
};