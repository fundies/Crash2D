#ifndef DRAWABLES_HPP
#define DRAWABLES_HPP

#include "segment.hpp"
#include "circle.hpp"
#include "polygon.hpp"

#include <SFML/Graphics.hpp>

class drawable : public sf::Drawable
{
public:
	drawable(sf::Color c) : _color(c) {}
	void SetColor(const sf::Color &c);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {}
	sf::Color _color;
};

/// Shape ///

class shape : virtual public Crash2D::Shape, public drawable
{
public:
	shape() : drawable(sf::Color::White) {};
};

/// Segment ///
class segment : public shape, public Crash2D::Segment
{
public:
	segment(const Crash2D::Vector2 &a, const Crash2D::Vector2 &b) : shape(), Segment(a, b) {}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

/// Circle ///
class circle : public shape, public Crash2D::Circle
{
public:
	circle(const Crash2D::Vector2 c, const Crash2D::Precision_t &r) : shape(), Circle(c, r) {}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

/// Polygon ///
class polygon : public shape, public Crash2D::Polygon
{
public:
	polygon() : shape(), Polygon() {}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // DRAWABLES_HPP
