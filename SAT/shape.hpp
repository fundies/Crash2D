#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "vector2.hpp"
#include "collision.hpp"
#include "projection.hpp"

class Shape : public sf::Drawable
{
public:
	Shape();
	virtual void setFillColor(sf::Color c);

protected:
	sf::Color _color;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}
};

#endif
