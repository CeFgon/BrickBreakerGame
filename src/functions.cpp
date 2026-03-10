#include "../headers/objects.h"

std::vector<sf::RectangleShape> generateBricks()
{
	std::vector<sf::RectangleShape> bricks;
	sf::RectangleShape rectangle({ 100.f, 20.f });
	float nextBrickPositionX = 0.f, nextBrickPositionY = 0.f;
	for (int j = 0; j < 9; ++j)
	{
		for (int i = 0; i <= 9; ++i)
		{
			rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
			if (i == 0)
			{
				rectangle.setPosition(sf::Vector2f({ nextBrickPositionX, nextBrickPositionY }));
				bricks.push_back(sf::RectangleShape(rectangle));
				nextBrickPositionX += 110.f;
			}
			else {
				rectangle.setPosition(sf::Vector2f({ nextBrickPositionX, nextBrickPositionY }));
				bricks.push_back(sf::RectangleShape(rectangle));
				nextBrickPositionX += 110.f;
			}
		}
		nextBrickPositionX = 0.f;
		nextBrickPositionY += 30.f;
	}
	return bricks;
}

void Ball::baseMove()
{
	this->ball.move({ this->moveDirectionX, this->moveDirectionY });
}

void Ball::setStartPosition(const sf::RenderWindow& window)
{
	this->ball.setPosition(sf::Vector2f({ window.getSize().x / 2 - 10.f, window.getSize().y / 2 - 0.f }));
}

void Ball::collisionCheck(const sf::RenderWindow& window, Platform* platform, std::vector<sf::RectangleShape>& bricks)
{
	if ((this->ball).getGlobalBounds().findIntersection(platform->getPlatformBody().getGlobalBounds())) {
		(this->moveDirectionY) = -3.f * (this->speedMultiplier);
		(this->moveDirectionX) = -1 + rand() % 3 * (this->speedMultiplier);
	}
	for (int i = 0; i < bricks.size(); ++i)
	{
		if ((this->ball).getGlobalBounds().findIntersection(bricks.at(i).getGlobalBounds())) {
			(this->moveDirectionY) = 3.f * (this->speedMultiplier);
			(this->moveDirectionX) = -1 + rand() % 3 * (this->speedMultiplier);
			bricks.erase(bricks.begin() + i);
			if ((this->speedMultiplier) < 3)
			{
				(this->speedMultiplier) += 0.05;
				platform->addToSpeedMultiplier(0.025);
			}
		}
	}
	if ((this->ball).getPosition().x + 15.f > window.getSize().x)
	{
		(this->ball).setPosition(sf::Vector2f({ (this->ball).getPosition().x - 1.f, (this->ball).getPosition().y }));
		(this->moveDirectionX) = -1 - rand() % 2 * (this->speedMultiplier);
	}
	if ((this->ball).getPosition().x - 15.f < 0.f)
	{
		(this->ball).setPosition(sf::Vector2f({ (this->ball).getPosition().x + 1.f, (this->ball).getPosition().y }));
		(this->moveDirectionX) = +1 + rand() % 2 * (this->speedMultiplier);
	}
	if ((this->ball).getPosition().y - 15.f < 0)
	{
		(this->moveDirectionY) = 3.f * (this->speedMultiplier);
		(this->moveDirectionX) = -1 + rand() % 3 * (this->speedMultiplier);
	}
	if ((this->ball).getPosition().y > window.getSize().y)
	{
		(this->ball).setPosition(sf::Vector2f({ 480.f, 300.f }));
		platform->setToStartPosition(window);
		(this->speedMultiplier) = 1;
		platform->setToStartSpeedMultiplier();
		(this->moveDirectionY) = 3.f;
		(this->moveDirectionX) = 0.f;
		//window.close();
	}
}

void Upgrade::baseMove()
{
	this->upgradeBody.move(sf::Vector2f({ 0.f, 2.f }));
}

void Upgrade::setBasePosition(float posX, float posY)
{
	this->upgradeBody.setPosition(sf::Vector2f({ posX - 0.f, posY - 0.f}));
}

void Upgrade::makeAction(std::vector<Ball> &balls)
{
	if (this->upgradeType == "tripleBall")
	{
		Ball newball;
		for (int i = 0; i < 2; ++i)
		{
			balls.push_back(newball);
		}
	}
}

void Platform::movePlatform(const sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (this->platformBody.getPosition().x + 105.f < window.getSize().x)
		{
			this->platformBody.move(sf::Vector2f({ 7.f * this->speedMultiplier, 0.f }));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		if (this->platformBody.getPosition().x - 5.f > 0.f)
		{
			this->platformBody.move(sf::Vector2f({ -7.f * this->speedMultiplier, 0.f }));
		}
	}
}