#ifndef DEMO_HPP
#define DEMO_HPP

#include <SFML/Graphics.hpp>

struct Demo {
	Demo(sf::RenderWindow &window) : window(window) {};
	virtual ~Demo() {};
	virtual void draw() = 0;
protected:
	sf::RenderWindow &window;
};

#endif