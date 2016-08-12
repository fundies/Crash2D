#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
	Circle(Precision_t radius);
	const Vector2 getCenter() const;
	void move(const Vector2 &offset);
	void move(Precision_t x, Precision_t y);
	Projection Project(Axis axis);
	Collision GetCollision(Circle c);
	const Precision_t& GetRadius() const;
	bool contains(Vector2 p);
	Circle& SetPos(const Vector2& _pos);
	const Vector2& GetPos() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Precision_t _radius;
	Vector2 _origin;
	Vector2 _pos;
};

#endif
