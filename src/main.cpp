#include "../headers/objects.h"

int main()
{
	//window
	sf::RenderWindow window(sf::VideoMode({ 980, 600 }), "SFML works!");
	window.setFramerateLimit(60);

	//bricks
	std::vector<sf::RectangleShape> bricks = generateBricks();

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
	//balls.at(0).setStartPosition(window);
	//sf::CircleShape ball(10.f);
	//ball.setPosition(sf::Vector2f({ window.getSize().x / 2 - 10.f, window.getSize().y / 2 - 0.f}));

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
			window.draw(bricks.at(i));
		}
		/*window.draw(upgrades.at(0).getUpgrade());
		upgrades.at(0).setupgradeType("tripleBall");
		upgrades.at(0).setActive(1);
		upgrades.at(0).makeAction(balls);*/

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

		//display
		window.display();
	}
}