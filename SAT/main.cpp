#include <iostream>
#include <math.h>
#include <limits>

#include "circle.hpp"
#include "polygon.hpp"

int main(int argc, char **argv)
{
	Polygon polygon;
	polygon.setFillColor(sf::Color::Red);
	polygon.setPointCount(3);
	polygon.setPoint(0, Vector2(500, 100));
	polygon.setPoint(1, Vector2(250, 500));
	polygon.setPoint(2, Vector2(750, 500));
	polygon.generateAxes();

	/*Polygon polygon2;
	polygon2.setFillColor(sf::Color::Green);
	polygon2.setPointCount(3);
	polygon2.setPoint(0, Vector2(200, 0));
	polygon2.setPoint(1, Vector2(400, 150));
	polygon2.setPoint(2, Vector2(250, 150));
	polygon2.generateAxes();*/
	
	Circle polygon2(60);
	polygon2.move(300,300);
	
	//Circle polygon2(15);

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

		//polygon2.rotate(rdir);

		polygon2.move(hdir*4, vdir*4);

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(polygon);
		window.draw(polygon2);

		Collision c = polygon.GetCollision(polygon2);

		if (c.IsTouching())
		{
			//polygon2.move(c.GetTranslation());
			polygon2.setFillColor(sf::Color::Blue);
		}
		else
		{
			polygon2.setFillColor(sf::Color::Green);
		}
		
		std::cout << (polygon.NearestVertex(Vector2(800,600)) == polygon.getPoint(2)) << std::endl;

		window.display();
	}

	return 0;
}