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
			/*if (i % 2 == 0)
			{
				rectangle.setFillColor(sf::Color::Red);
			}
			else {
				rectangle.setFillColor(sf::Color::Green);
			}*/
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