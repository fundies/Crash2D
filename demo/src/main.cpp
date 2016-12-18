#include "drawables.hpp"

#include <iostream>
#include <random>


int rand(int min, int max)
{
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(min, max);

	int r = dist(engine);

	if ( r != 0)
		return r;

	else
		return rand(min, max);
}

int main(int argc, char **argv)
{
	//circle A(100);
	//segment A(Vector2(0, 0), Vector2(800, 600));
	polygon A;
	A.SetPointCount(3);
	A.SetPoint(0, Vector2(0, 0));
	A.SetPoint(1, Vector2(180, 0));
	A.SetPoint(2, Vector2(150, 150));
	A.ReCalc();

	A.SetPos(Vector2(300, 300));
	A.SetColor(sf::Color::Green);

	//circle B(35);
	segment B(Vector2(0, 0), Vector2(220, -30));
	/*polygon B;
	B.SetPointCount(3);
	B.SetPoint(0, Vector2(0, 0));
	B.SetPoint(1, Vector2(80, 0));
	B.SetPoint(2, Vector2(50, 50));
	B.ReCalc();*/

	B.SetColor(sf::Color::Red);

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

		B.Move(Vector2(hdir * 4, vdir * 4));

		if (A.Contains(B))
		{
			B.SetColor(sf::Color::Blue);
		}

		else if (A.Intersects(B))
		{
			B.SetColor(sf::Color(255, 255, 0, 200));
		}

		else
			B.SetColor(sf::Color::Red);


		window.draw(A);
		window.draw(B);

		//std::cout << "begin" << std::endl;

		for (auto && p : A.GetIntersections(B))
		{
			//std::cout << "(" << p.x << "," << p.y << ")" << std::endl;
			circle c(3);
			c.SetPos(p);
			c.SetColor(sf::Color::Red);

			window.draw(c);
		}

		if (A.Intersects(B) || A.Contains(B))
		{
			auto t = B;
			t.Move(A.GetTranslation(B));
			t.SetColor(sf::Color(255, 0, 255, 50));

			window.draw(t);

			/*circle c(3);
			c.SetPos(B.GetPos() + B.GetTranslation(A));
			c.SetColor(sf::Color::Magenta);

			window.draw(c);*/
		}

		circle c1(3);
		c1.SetPos(A.GetPos() + A.GetCenter());
		c1.SetColor(sf::Color::Magenta);

		window.draw(c1);

		circle c(3);
		c.SetPos(B.GetPos() + B.GetCenter());
		c.SetColor(sf::Color::Magenta);

		window.draw(c);

		//std::cout << "end" << std::endl;


		window.display();
	}
}
