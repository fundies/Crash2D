#include <iostream>

#include "polygon.hpp"

int main(int argc, char **argv)
{
	// 16,0 0,32 32,32 16,0
	Polygon polygon;
	polygon.setFillColor(sf::Color::Green);
	polygon.setPointCount(3);
	polygon.setPoint(0, Vector2(16*4, 0));
	polygon.setPoint(1, Vector2(0, 32*4));
	polygon.setPoint(2, Vector2(32*4, 32*4));
	polygon.generateAxes();

	// 16,0 48,0 64,16 64,48 48,64 16,64 0,48 0,16 16,0
	Polygon polygon2;
	polygon2.setFillColor(sf::Color::Red);
	polygon2.setPointCount(8);
	polygon2.setPoint(0, Vector2(16*5, 0)); //16,0
	polygon2.setPoint(1, Vector2(48*5, 0)); //48,0
	polygon2.setPoint(2, Vector2(64*5, 16*5)); //64,16
	polygon2.setPoint(3, Vector2(64*5, 48*5)); //64,48
	polygon2.setPoint(4, Vector2(48*5, 64*5)); //48,64
	polygon2.setPoint(5, Vector2(16*5, 64*5)); // 16,64
	polygon2.setPoint(6, Vector2(0, 48*5)); // 0,48
	polygon2.setPoint(7, Vector2(0, 16*5)); // 0,16

	polygon2.move(250, 150);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Collision Test");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		int hdir = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		int vdir = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		int rdir = sf::Keyboard::isKeyPressed(sf::Keyboard::Z) - sf::Keyboard::isKeyPressed(sf::Keyboard::X);

		polygon.rotate(rdir);

		polygon.move(hdir*4, vdir*4);

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(polygon2);
		window.draw(polygon);

		Collision c = polygon.GetCollision(polygon2);

		if (c.IsTouching())
		{
			//polygon.move(c.GetTranslation());

			if (c.IsContained())
				polygon.setFillColor(sf::Color::Magenta);
			else
				polygon.setFillColor(sf::Color::Blue);
		}
		else
		{
			polygon.setFillColor(sf::Color::Green);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			polygon.move(c.GetTranslation());

		window.display();
	}

	return 0;
}
