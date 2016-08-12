#include "circle.hpp"

#include <cmath>
#include <iostream>

Circle::Circle(Precision_t radius) : Shape()
{
	_origin = Vector2(radius, radius);
	_radius = radius;
}

const Vector2 Circle::getCenter() const
{
	return _pos;
}

void Circle::move(const Vector2 &offset)
{
	_pos += offset;
}

void Circle::move(Precision_t x, Precision_t y)
{
	_pos += Vector2(x, y);
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape circle(_radius, 30);
	circle.setOrigin(_origin.asFloat());
	circle.setPosition(_pos.asFloat());
	circle.setFillColor(_color);
	target.draw(circle);
}

Projection Circle::Project(Axis axis)
{
	Precision_t v = axis.dot(getCenter());
	return Vector2(v - GetRadius(), v + GetRadius());
}

Collision Circle::GetCollision(Circle c)
{
	
	Vector2 v = c.getCenter() - getCenter();
	
	Precision_t radiiSum = GetRadius() + c.GetRadius();
	Precision_t dist = v.magnitude();
	Precision_t tDist = radiiSum - dist;
	
	Precision_t theta = atan2(v.y, v.x);
	
	Precision_t x = tDist * std::cos(theta);
	Precision_t y = tDist * std::sin(theta);
	
	Vector2 translation(x, y);
	if (translation.dot(v) < 0)
		translation = -translation;
	
	Precision_t radiiDif = std::abs(GetRadius() - c.GetRadius());
	bool contained = (dist <= radiiDif);
	bool overlap = (dist < radiiSum);
	
	return Collision(translation, overlap, contained);
}

const Precision_t& Circle::GetRadius() const
{
	return _radius;
}

Circle& Circle::SetPos(const Vector2& _pos) 
{
	this->_pos = _pos;
	return *this;
}

const Vector2& Circle::GetPos() const 
{
	return _pos;
}

bool Circle::contains(Vector2 p)
{
	Vector2 v = getCenter() - p;
	Precision_t dist = v.magnitude();
 
	return (dist < GetRadius());
}