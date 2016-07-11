#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "vector2.hpp"
#include "collision.hpp"
#include "projection.hpp"

class Polygon : public sf::Drawable
{
private:
	AxesVec axes;
	std::vector<Vector2> _points;
	sf::Color _color;

public:
	Polygon();
	const AxesVec& GetAxes() const;
	const unsigned getPointCount() const;
	Vector2 getPoint(unsigned index);
	void generateAxes();
	void move(const Vector2 &offset);
	void move(Precision_t x, Precision_t y);
	const Vector2 getOrigin() const;
	void setFillColor(sf::Color c);
	void setPointCount(unsigned c);
	void setPoint(unsigned i, Vector2 p);
	void rotate(Precision_t angle);
	Projection Project(Axis axis);
	Collision GetCollision(Polygon p);
	bool contains(Vector2 p);
	bool contains(Polygon p);

private:
	bool triangleContains(Vector2 p, Vector2 a, Vector2 b, Vector2 c);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
