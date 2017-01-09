#include "drawables.hpp"
#include "collision.hpp"

#include <iostream>
#include <random>
#include <memory>

int rand(int min, int max)
{
	int n = max - min + 1;
	int remainder = RAND_MAX % n;
	int x;

	do
	{
		x = rand();
	}
	while (x >= RAND_MAX - remainder);

	return min + x % n;
}

using Shape_ptr = std::unique_ptr<shape>;

int main(int argc, char **argv)
{
	std::vector<Shape_ptr> vecA(3);
	vecA[0] = Shape_ptr(new circle(Vector2(100, 100), 30));

	vecA[1] = Shape_ptr(new polygon());
	vecA[1]->SetPointCount(3);
	vecA[1]->SetPoint(0, Vector2(0, 0));
	vecA[1]->SetPoint(1, Vector2(180, 0));
	vecA[1]->SetPoint(2, Vector2(150, 150));
	vecA[1]->ReCalc();

	vecA[2] = Shape_ptr(new segment(Vector2(0, 0), Vector2(100, 300)));

	std::vector<Shape_ptr> vecB(3);
	vecB[0] = Shape_ptr(new circle(Vector2(0, 0), 30));

	vecB[1] = Shape_ptr(new polygon());
	vecB[1]->SetPointCount(3);
	vecB[1]->SetPoint(0, Vector2(0, 0));
	vecB[1]->SetPoint(1, Vector2(80, 0));
	vecB[1]->SetPoint(2, Vector2(50, 50));
	vecB[1]->ReCalc();

	vecB[2] = Shape_ptr(new segment(Vector2(0, 0), Vector2(100, 30)));

	int ShapeA = 1;
	int ShapeB = 2;

	vecA[ShapeA]->SetColor(sf::Color::Green);
	vecB[ShapeB]->SetColor(sf::Color::Red);

	vecA[ShapeA]->Move(Vector2(rand(0, 600), rand(0, 600)));
	vecB[ShapeB]->Move(Vector2((vecA[ShapeA]->GetPos().x + vecA[ShapeA]->GetCenter().x) + 2, (vecA[ShapeA]->GetPos().y + vecA[ShapeA]->GetCenter().y) - 2));

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

		// clear the window with black color
		window.clear(sf::Color::Black);

		// Move
		int hdir = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		int vdir = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

		vecB[ShapeB]->Move(Vector2(hdir * 4, vdir * 4));

		Collision collision = vecA[ShapeA]->GetCollision(*vecB[ShapeB]);
		//polygon a = *(polygon*)vecA[ShapeA].get();
		//segment b = *(segment*)vecB[ShapeB].get();
		//Collision collision = a.GetCollision(b);

		if (collision.AcontainsB())
		{
			vecB[ShapeB]->SetColor(sf::Color::Blue);
		}

		else if (collision.Overlaps())
		{
			vecB[ShapeB]->SetColor(sf::Color(255, 255, 0, 200));
		}

		else

			vecB[ShapeB]->SetColor(sf::Color::Red);

		window.draw(*vecA[ShapeA]);
		window.draw(*vecB[ShapeB]);


		for (auto && p : collision.GetIntersects())
		{
			circle c(Vector2(0, 0), 3);
			c.Circle::SetPos(p);
			c.SetColor(sf::Color::Red);

			window.draw(c);
		}


		if (collision.Overlaps() || collision.AcontainsB())
		{
			vecB[ShapeB]->Move(collision.GetDisplacement());
			vecB[ShapeB]->SetColor(sf::Color(255, 0, 255, 50));

			window.draw(*vecB[ShapeB]);

			vecB[ShapeB]->Move(-collision.GetDisplacement());
		}

		circle c1(Vector2(0, 0), 3);
		c1.Circle::SetPos(vecA[ShapeA]->GetPos() + vecA[ShapeA]->GetCenter());
		c1.SetColor(sf::Color::Magenta);

		window.draw(c1);

		circle c(Vector2(0, 0), 3);
		c.Circle::SetPos(vecB[ShapeB]->GetPos() + vecB[ShapeB]->GetCenter());
		c.SetColor(sf::Color::Magenta);

		window.draw(c);

		window.display();
	}
}
