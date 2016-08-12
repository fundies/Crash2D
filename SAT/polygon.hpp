#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "shape.hpp"
#include "circle.hpp"

class Polygon : public Shape
{
public:
	Polygon() : Shape() {}
	const AxesVec& GetAxes() const;
	const unsigned getPointCount() const;
	const Vector2 getPoint(unsigned index) const;
	void generateAxes();
	void move(const Vector2 &offset);
	void move(Precision_t x, Precision_t y);
	const Vector2 getCenter() const;
	void setPointCount(unsigned c);
	void setPoint(unsigned i, Vector2 p);
	void rotate(Precision_t angle);
	Projection Project(Axis axis);
	Collision GetCollision(Polygon p);
	Collision GetCollision(Circle c);
	bool contains(Vector2 p);
	bool contains(Polygon p);
	Polygon& SetPos(const Vector2& _pos);
	const Vector2& GetPos() const;
	Vector2 NearestVertex(Vector2 point);
	
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool triangleContains(Vector2 p, Vector2 a, Vector2 b, Vector2 c);
	Precision_t GetDistance(Vector2 a, Vector2 b);

	AxesVec _axes;
	std::vector<Vector2> _points;
	Vector2 _pos;
};

#endif
