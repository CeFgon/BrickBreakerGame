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

	void ballBaseMove()
	{
		this->ball.move({ this->ballMoveDirectionX, this->ballMoveDirectionY });
	}

	void setBallStartPosition(const sf::RenderWindow& window)
	{
		ball.setPosition(sf::Vector2f({ window.getSize().x / 2 - 10.f, window.getSize().y / 2 - 0.f }));
	}

	sf::CircleShape getBall()
	{
		return ball;
	}

	float getBallMoveDirectionX()
	{
		return this->ballMoveDirectionX;
	}

	float getBallMoveDirectionY()
	{
		return this->ballMoveDirectionY;
	}

	float getBallSpeedMultiplier()
	{
		return this->ballSpeedMultiplier;
	}

	void ballCollisionCheck(sf::RenderWindow* window, sf::RectangleShape* platform, std::vector<sf::RectangleShape>& bricks, float* platformSpeedMultiplier) {
		if ((this->ball).getGlobalBounds().findIntersection((*platform).getGlobalBounds())) {
			(this->ballMoveDirectionY) = -3.f * (this->ballSpeedMultiplier);
			(this->ballMoveDirectionX) = -1 + rand() % 3 * (this->ballSpeedMultiplier);
		}
		for (int i = 0; i < bricks.size(); ++i)
		{
			if ((this->ball).getGlobalBounds().findIntersection(bricks.at(i).getGlobalBounds())) {
				(this->ballMoveDirectionY) = 3.f * (this->ballSpeedMultiplier);
				(this->ballMoveDirectionX) = -1 + rand() % 3 * (this->ballSpeedMultiplier);
				bricks.erase(bricks.begin() + i);
				if ((this->ballSpeedMultiplier) < 3)
				{
					(this->ballSpeedMultiplier) += 0.05;
					(*platformSpeedMultiplier) += 0.025;
				}
			}
		}
		if ((this->ball).getPosition().x + 15.f > (*window).getSize().x)
		{
			(this->ball).setPosition(sf::Vector2f({ (this->ball).getPosition().x - 1.f, (this->ball).getPosition().y }));
			(this->ballMoveDirectionX) = -1 - rand() % 2 * (this->ballSpeedMultiplier);
		}
		if ((this->ball).getPosition().x - 15.f < 0.f)
		{
			(this->ball).setPosition(sf::Vector2f({ (this->ball).getPosition().x + 1.f, (this->ball).getPosition().y }));
			(this->ballMoveDirectionX) = +1 + rand() % 2 * (this->ballSpeedMultiplier);
		}
		if ((this->ball).getPosition().y - 15.f < 0)
		{
			(this->ballMoveDirectionY) = 3.f * (this->ballSpeedMultiplier);
			(this->ballMoveDirectionX) = -1 + rand() % 3 * (this->ballSpeedMultiplier);
		}
		if ((this->ball).getPosition().y > (*window).getSize().y)
		{
			(this->ball).setPosition(sf::Vector2f({ 480.f, 300.f }));
			(*platform).setPosition(sf::Vector2f({ (*window).getSize().x / 2 - 50.f , (*window).getSize().y - 40.f }));
			(this->ballSpeedMultiplier) = 1;
			(*platformSpeedMultiplier) = 1;
			(this->ballMoveDirectionY) = 3.f;
			(this->ballMoveDirectionX) = 0.f;
			//window.close();
		}
	}

};

std::vector<sf::RectangleShape> generateBricks();