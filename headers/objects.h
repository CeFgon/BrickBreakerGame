#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Ball;

class Platform {
private:
	sf::RectangleShape platformBody;
	float speedMultiplier;
public:
	Platform() : platformBody(sf::Vector2f({ 100.f, 20.f })) {
		this->speedMultiplier = 1;
	}

	sf::RectangleShape getPlatformBody()
	{
		return this->platformBody;
	}

	float getSpeedMultiplier() const
	{
		return this->speedMultiplier;
	}

	void setToStartPosition(const sf::RenderWindow& window)
	{
		this->platformBody.setPosition(sf::Vector2f({ window.getSize().x / 2 - 50.f , window.getSize().y - 40.f }));
	}

	void setToStartSpeedMultiplier()
	{
		this->speedMultiplier = 1;
	}

	void addToSpeedMultiplier(float multiplier)
	{
		this->speedMultiplier += multiplier;
	}

	void movePlatform(const sf::RenderWindow& window);
};

class Upgrade {
private:
	sf::RectangleShape upgradeBody;
	std::string upgradeType;
	int isActive = 0;
public:
	Upgrade() : upgradeBody(sf::Vector2f({ 30.f, 20.f })) {
		upgradeBody.setFillColor(sf::Color::Yellow);
	}

	sf::RectangleShape getUpgrade()
	{
		return this->upgradeBody;
	}

	std::string getUpgradeType()
	{
		return this->upgradeType;
	}

	float getStatus() const
	{
		return this->isActive;
	}

	void setActive(const int activeCode)
	{
		this->isActive = activeCode;
	}

	void setupgradeType(std::string type)
	{
		this->upgradeType = type;
	}

	void baseMove();

	void setBasePosition(float posX, float posY);

	void makeAction(std::vector<Ball>& balls);
};

class Brick {
private:
	sf::RectangleShape brickBody;
	Upgrade upgrade;

public:
	Brick() : brickBody(sf::Vector2f({ 100.f, 20.f }))
	{
	}

	sf::RectangleShape& getBrickBody()
	{
		return this->brickBody;
	}

	Upgrade getBrickUpgrade()
	{
		return this->upgrade;
	}
};

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

	float getMoveDirectionX() const
	{
		return this->moveDirectionX;
	}

	float getMoveDirectionY() const
	{
		return this->moveDirectionY;
	}

	float getSpeedMultiplier() const
	{
		return this->speedMultiplier;
	}

	void baseMove();

	void setStartPosition(const sf::RenderWindow& window);

	void collisionCheck(const sf::RenderWindow& window, Platform* platform, std::vector<Brick>& bricks);
};

void generateBricks(std::vector<Brick>& bricks);