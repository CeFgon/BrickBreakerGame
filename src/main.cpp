#include <SFML/Graphics.hpp>
#include <vector>

std::vector<sf::RectangleShape> generateBricks();
void ballCollisionCheck(sf::RenderWindow* window, sf::CircleShape* ball, sf::RectangleShape *platform, std::vector<sf::RectangleShape> &bricks, float* ballMoveDirectionX, float* ballMoveDirectionY, float* ballSpeedMultiplier, float* platformSpeedMultiplier);

int main()
{
	//window
	sf::RenderWindow window(sf::VideoMode({ 980, 600 }), "SFML works!");
	window.setFramerateLimit(60);

	//bricks
	std::vector<sf::RectangleShape> bricks = generateBricks();

	//platform thing
	sf::RectangleShape platform({ 100.f, 20.f });
	platform.setPosition(sf::Vector2f({ window.getSize().x / 2 - 50.f , window.getSize().y - 40.f }));

	//ball(s)
	sf::CircleShape ball(10.f);
	ball.setPosition(sf::Vector2f({ window.getSize().x / 2 - 10.f, window.getSize().y / 2 - 0.f}));
	float ballMoveDirectionY = 3.f, ballMoveDirectionX = 0.f;
	float ballSpeedMultiplier = 1, platformSpeedMultiplier = 1;

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		for (int i = 0; i < bricks.size(); ++i)
		{
			window.draw(bricks.at(i));
		}

		//platform move
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			if (platform.getPosition().x + 105.f < window.getSize().x)
			{
				platform.move(sf::Vector2f({ 7.f * platformSpeedMultiplier, 0.f }));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			if (platform.getPosition().x - 5.f > 0.f)
			{
				platform.move(sf::Vector2f({ -7.f * platformSpeedMultiplier, 0.f }));
			}
		}

		ballCollisionCheck(&window, &ball, &platform, bricks, &ballMoveDirectionX, &ballMoveDirectionY, &ballSpeedMultiplier, &platformSpeedMultiplier);

		window.draw(platform);
		ball.move({ ballMoveDirectionX, ballMoveDirectionY });
		window.draw(ball);
		window.display();
	}
}

std::vector<sf::RectangleShape> generateBricks() {
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

void ballCollisionCheck(sf::RenderWindow *window, sf::CircleShape *ball, sf::RectangleShape *platform, std::vector<sf::RectangleShape> &bricks, float *ballMoveDirectionX, float *ballMoveDirectionY, float *ballSpeedMultiplier, float* platformSpeedMultiplier) {
	if ( (*ball).getGlobalBounds().findIntersection((*platform).getGlobalBounds()) ) {
		(*ballMoveDirectionY) = -3.f * (*ballSpeedMultiplier);
		(*ballMoveDirectionX) = -1 + rand() % 3 * (*ballSpeedMultiplier);
	}
	for ( int i = 0; i < bricks.size(); ++i )
	{
		if ( (*ball).getGlobalBounds().findIntersection(bricks.at(i).getGlobalBounds()) ) {
			(*ballMoveDirectionY) = 3.f * (*ballSpeedMultiplier);
			(*ballMoveDirectionX) = -1 + rand() % 3 * (*ballSpeedMultiplier);
			bricks.erase(bricks.begin() + i);
			if ( (*ballSpeedMultiplier) < 3 )
			{
				(*ballSpeedMultiplier) += 0.05;
				(*platformSpeedMultiplier) += 0.025;
			}
		}
	}
	if ( (*ball).getPosition().x + 15.f > (*window).getSize().x )
	{
		(*ball).setPosition(sf::Vector2f({ (*ball).getPosition().x - 1.f, (*ball).getPosition().y }));
		(*ballMoveDirectionX) = -1 - rand() % 2 * (*ballSpeedMultiplier);
	}
	if ( (*ball).getPosition().x - 15.f < 0.f )
	{
		(*ball).setPosition(sf::Vector2f({ (*ball).getPosition().x + 1.f, (*ball).getPosition().y }));
		(*ballMoveDirectionX) = +1 + rand() % 2 * (*ballSpeedMultiplier);
	}
	if ( (*ball).getPosition().y - 15.f < 0 )
	{
		(*ballMoveDirectionY) = 3.f * (*ballSpeedMultiplier);
		(*ballMoveDirectionX) = -1 + rand() % 3 * (*ballSpeedMultiplier);
	}
	if ( (*ball).getPosition().y > (*window).getSize().y )
	{
		(*ball).setPosition(sf::Vector2f({ 480.f, 300.f }));
		(*platform).setPosition(sf::Vector2f({ (*window).getSize().x / 2 - 50.f , (*window).getSize().y - 40.f }));
		(*ballSpeedMultiplier) = 1;
		(*platformSpeedMultiplier) = 1;
		(*ballMoveDirectionY) = 3.f;
		(*ballMoveDirectionX) = 0.f;
		//window.close();
	}
}