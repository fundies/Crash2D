#include "shape.hpp"

#include <cmath>
#include <limits>

Shape::Shape()
{
	_color = sf::Color::White;
}

void Shape::setFillColor(sf::Color c)
{
	_color = c;
}
