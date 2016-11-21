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

/*int main(int argc, char **argv)
{
	std::vector<polygon*> polygons;
	std::vector<circle*> circles;

	for (unsigned i = 0; i < 10; ++i)
	{
		polygon* pA = new polygon();
		pA->SetPointCount(3);
		pA->SetPoint(0, Vector2(60, 0));
		pA->SetPoint(1, Vector2(90, 30));
		pA->SetPoint(2, Vector2(0, 30));

		pA->SetPos(Vector2(rand(0, 800), rand(0, 600)));
		pA->SetColor(sf::Color(rand(0, 255), rand(0, 255), rand(0, 255)));

		pA->hspeed = rand(-1, 1);
		pA->vspeed = rand(-1, 1);

		pA->SetRotation(rand(0, 360));
		pA->ReCalc();

		polygons.push_back(pA);

		circle* c = new circle(rand(8, 15));
		c->SetPos(Vector2(rand(0, 800), rand(0, 600)));
		//c->hspeed = rand(-1, 1);
		//c->vspeed = rand(-1, 1);
		c->SetColor(sf::Color(rand(0, 255), rand(0, 255), rand(0, 255)));

		circles.push_back(c);
	}

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

		// draw everything here...)

		for(auto && p : polygons)
		{
			Vector2 pos = p->GetPos();

			if (pos.x < 0)
				p->hspeed = std::abs(p->hspeed);

			else if (pos.x > 800)
				p->hspeed = -std::abs(p->hspeed);

			if (pos.y < 0)
				p->vspeed = std::abs(p->vspeed);

			else if (pos.y > 600)
				p->vspeed = -std::abs(p->vspeed);


			p->Rotate(1);
			p->ReCalc();

			for(auto && c : circles)
			{

				Collision col = p->GetCollision(*c);

				if (col.IsTouching())
				{
					p->Move(col.GetTranslation() * -1);
					p->hspeed = -p->hspeed;
					p->vspeed = -p->vspeed;
					c->SetColor(sf::Color(rand(0, 255), rand(0, 255), rand(0, 255)));
				}
			}

			for(auto && c : polygons)
			{
				if (c != p)
				{
					Collision col = p->GetCollision(*c);

					if (col.IsTouching())
					{
						c->Move(col.GetTranslation());
						c->hspeed = -c->hspeed;
						c->vspeed = -c->vspeed;
						p->hspeed = -p->hspeed;
						p->vspeed = -p->vspeed;
						c->SetColor(sf::Color(rand(0, 255), rand(0, 255), rand(0, 255)));
					}
				}
			}

			p->Move(Vector2(p->hspeed, p->vspeed));
			window.draw(*p);
		}

		for(auto && c : circles)
		{
			//c->Move(Vector2(p->hspeed, p->vspeed));
			window.draw(*c);
		}

		window.display();
	}

	return 0;
}*/

int main(int argc, char **argv)
{
	circle A(100);
	A.SetPos(Vector2(300, 300));
	A.SetColor(sf::Color::Green);

	circle B(50);
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

		else
			B.SetColor(sf::Color::Red);

		// draw everything here...)
		window.draw(A);
		window.draw(B);

		window.display();
	}
}
