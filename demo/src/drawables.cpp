#include "drawables.hpp"

/// Line ///
void line::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray line(sf::Lines, 2);

	sf::Vector2f a(GetTransformedPoint(0).x, GetTransformedPoint(0).y);
	sf::Vector2f b(GetTransformedPoint(1).x, GetTransformedPoint(1).y);

	line[0] = sf::Vertex(a, _color);
	line[1] = sf::Vertex(b, _color);

	target.draw(line);
}

void line::SetColor(const sf::Color &c)
{
	_color = c;
}

/// Circle ///
void circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape circle(GetRadius(), 30);

	sf::Vector2f a(GetCenter().x, GetCenter().y);
	sf::Vector2f b(GetPos().x, GetPos().y);

	circle.setOrigin(a);
	circle.setPosition(b);
	circle.setFillColor(_color);

	target.draw(circle);
}

void circle::SetColor(const sf::Color &c)
{
	_color = c;
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

void polygon::SetColor(const sf::Color &c)
{
	_color = c;
}
