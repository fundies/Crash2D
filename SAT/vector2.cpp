#include "vector2.hpp"

#include <cmath>

Vector2 Vector2::perpendicular()
{
	return Vector2(y, -x);
}

Precision_t Vector2::dot(Vector2 v)
{
	return (x * v.x) + (y * v.y);
}

Precision_t Vector2::magnitude()
{
	return std::sqrt(dot(*this));
}

Vector2 Vector2::normalize()
{
	return *this / magnitude();
}

Vector2::Vector2(const sf::Vector2<Precision_t> &v)
{
	x = v.x;
	y = v.y;
}
