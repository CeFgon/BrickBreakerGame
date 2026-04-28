#include "../headers/objects.h"

int main()
{
	//window
	sf::RenderWindow window(sf::VideoMode({ 980, 600 }), "SFML works!");
	window.setFramerateLimit(60);

	//bricks
	std::vector<Brick> bricks;
	generateBricks(bricks);

	//platform thing
	Platform platform;
	platform.setToStartPosition(window);

	//ball(s)
	std::vector<Ball> balls;
	Ball ball;
	balls.push_back(ball);
	for (int i = 0; i < balls.size(); ++i) {
		balls.at(i).setStartPosition(window);
	}

	//upgrades
	std::vector<Upgrade> upgrades;
	Upgrade upgrade;
	upgrade.setBasePosition(40.f, window.getSize().y - 40.f);
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
			window.draw(bricks.at(i).getBrickBody());
		}
		/*
		window.draw(upgrades.at(0).getUpgrade());
		upgrades.at(0).setupgradeType("tripleBall");
		upgrades.at(0).setActive(1);
		upgrades.at(0).makeAction(balls);
		*/

		//balls move
		for (int i = 0; i < balls.size(); ++i) {
			balls.at(i).baseMove();
		}

		//platform move
		platform.movePlatform(window);

		//balls collision check
		for (int i = 0; i < balls.size(); ++i) {
			balls.at(i).collisionCheck(window, &platform, bricks);
		}

		//drawing platform and balls
		window.draw(platform.getPlatformBody());
		for (int i = 0; i < balls.size(); ++i) {
			window.draw(balls.at(i).getBall());
		}

		/*
		sf::RectangleShape randomRect(sf::Vector2f({ 100.f, 30.f}));
		randomRect.setFillColor(sf::Color::Red);
		for (int i = 1; i < 9; i++)
		{
			randomRect.setPosition(sf::Vector2f({ 0.f, 0.f + (i * 30.f) }));
		}
		window.draw(randomRect);
		*/

		//display
		window.display();
	}
}