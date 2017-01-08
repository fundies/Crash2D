#include "drawables.hpp"

#include <iostream>

/// Shape ///
void drawable::SetColor(const sf::Color &c)
{
	_color = c;
}


/// Segment ///
void segment::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray segment(sf::Lines, 2);

	sf::Vector2f a(GetTransformedPoint(0).x, GetTransformedPoint(0).y);
	sf::Vector2f b(GetTransformedPoint(1).x, GetTransformedPoint(1).y);

	segment[0] = sf::Vertex(a, _color);
	segment[1] = sf::Vertex(b, _color);

	target.draw(segment);
}

/// Circle ///
void circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape circle(GetRadius(), 30);

	sf::Vector2f a(GetRadius(), GetRadius());
	sf::Vector2f b(GetCenter().x + GetPos().x, GetCenter().y + GetPos().y);

	circle.setOrigin(a);
	circle.setPosition(b);
	circle.setFillColor(_color);

	target.draw(circle);
}

/// Polygon ///
void polygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray a(sf::TrianglesFan, _points.size() + 2);

	sf::Vector2f v1(GetPoint(0).x, GetPoint(0).y);
	sf::Vector2f v2(GetPos().x, GetPos().y);

	a[0] = sf::Vertex(v1 + v2, _color);

	for(unsigned p = 0; p < GetPointCount(); ++p)
	{
		v1 = sf::Vector2f(GetPoint(p).x, GetPoint(p).y);
		a[p + 1] = sf::Vertex(v1 + v2, _color);
	}

	v1 = sf::Vector2f(GetPoint(0).x, GetPoint(0).y);
	a[GetPointCount() + 1] = sf::Vertex(v1 + v2, _color);

	target.draw(a);
}
