#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

std::vector<sf::RectangleShape> generateBricks();

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

	float getSpeedMultiplier()
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

	void collisionCheck(const sf::RenderWindow& window, Platform* platform, std::vector<sf::RectangleShape>& bricks);
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

	void setupgradeType(std::string type)
	{
		this->upgradeType = type;
	}

	void baseMove();

	void setBasePosition(float posX, float posY);

	void makeAction(std::vector<Ball>& balls);
};