#include "segment.hpp"
#include "circle.hpp"
#include "polygon.hpp"

#include <SFML/Graphics.hpp>

/// Segment ///
class segment : public Segment, public sf::Drawable
{
public:
	segment(const Vector2 &a, const Vector2 &b) : Segment(a, b), _color(sf::Color::White) {}
	void SetColor(const sf::Color &c);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Color _color;
};

/// Circle ///
class circle : public Circle, public sf::Drawable
{
public:
	circle(const Precision_t &r) : Circle(r), _color(sf::Color::White) {}
	void SetColor(const sf::Color &c);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Color _color;

};

/// Polygon ///
class polygon : public Polygon, public sf::Drawable
{
public:
	polygon() : Polygon(), _color(sf::Color::White) {}
	void SetColor(const sf::Color &c);

	int hspeed;
	int vspeed;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Color _color;

};
