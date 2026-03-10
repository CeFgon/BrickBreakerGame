#include "../headers/objects.h"

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
	float platformSpeedMultiplier = 1;

	//ball(s)
	std::vector<Ball> balls;
	Ball ball;
	balls.push_back(ball);
	balls.at(0).setStartPosition(window);
	//sf::CircleShape ball(10.f);
	//ball.setPosition(sf::Vector2f({ window.getSize().x / 2 - 10.f, window.getSize().y / 2 - 0.f}));

	//upgrades
	std::vector<Upgrade> upgrades;
	Upgrade upgrade;
	upgrades.push_back(upgrade);

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

		for (int i = 0; i < balls.size(); ++i) {
			balls.at(i).collisionCheck(&window, &platform, bricks, &platformSpeedMultiplier);
		}

		window.draw(platform);
		for (int i = 0; i < balls.size(); ++i) {
			balls.at(i).baseMove();
		}
		for (int i = 0; i < balls.size(); ++i) {
			window.draw(balls.at(i).getBall());
		}
		window.display();
	}
}