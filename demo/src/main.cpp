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
	vecA[0] = Shape_ptr(new circle(Vector2(300, 400), 150));

	vecA[1] = Shape_ptr(new polygon());
	vecA[1]->SetPointCount(4);
	vecA[1]->SetPoint(0, Vector2(250, 250));
	vecA[1]->SetPoint(1, Vector2(350, 250));
	vecA[1]->SetPoint(2, Vector2(350, 350));
	vecA[1]->SetPoint(3, Vector2(250, 350));
	vecA[1]->ReCalc();

	vecA[2] = Shape_ptr(new segment(Vector2(400, 300), Vector2(500, 300)));

	std::vector<Shape_ptr> vecB(3);
	vecB[0] = Shape_ptr(new circle(Vector2(400, 300), 50));

	vecB[1] = Shape_ptr(new polygon());
	vecB[1]->SetPointCount(3);
	vecB[1]->SetPoint(0, Vector2(350, 300));
	vecB[1]->SetPoint(1, Vector2(400, 300));
	vecB[1]->SetPoint(2, Vector2(325, 350));
	vecB[1]->ReCalc();

	vecB[2] = Shape_ptr(new segment(Vector2(450, 250), Vector2(450, 350)));

	int ShapeA = 1;
	int ShapeB = 2;

	vecA[ShapeA]->SetColor(sf::Color::Green);
	vecB[ShapeB]->SetColor(sf::Color::Red);


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

		// Scale
		int scl = sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);

		// Rot
		int rot = sf::Keyboard::isKeyPressed(sf::Keyboard::X) - sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

		Transformation t;
		t.Translate(Vector2(hdir * 4, vdir * 4));
		t.SetPivot(vecB[ShapeB]->GetCenter());
		t.Rotate(rot);
		t.Scale(scl * 0.1);

		vecB[ShapeB]->Transform(t);

		Collision collision = vecA[ShapeA]->GetCollision(*vecB[ShapeB]);

		if (vecA[ShapeA]->Contains(*vecB[ShapeB]))
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
			circle c(p,  3);
			c.SetColor(sf::Color::Red);
			window.draw(c);
		}

		if (collision.Overlaps() || collision.AcontainsB())
		{
			Transformation t;

			t.Translate(collision.GetDisplacement());
			vecB[ShapeB]->Transform(t);
			vecB[ShapeB]->SetColor(sf::Color(255, 0, 255, 50));

			window.draw(*vecB[ShapeB]);

			t.Translate(-collision.GetDisplacement());
			t.Translate(-collision.GetDisplacement());
			vecB[ShapeB]->Transform(t);
		}

		circle c1(vecA[ShapeA]->GetCenter(), 3);
		c1.SetColor(sf::Color::Magenta);

		circle c2(vecB[ShapeB]->GetCenter(), 3);
		c2.SetColor(sf::Color::Magenta);

		window.draw(c1);
		window.draw(c2);

		window.display();
	}
}
