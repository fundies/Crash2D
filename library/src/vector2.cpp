#include "vector2.hpp"

#include <cmath>
#include <iostream>

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(const Precision_t x, const Precision_t y) : x(x), y(y)
{
}

const Vector2 Vector2::Perpendicular() const
{
	return Vector2(y, -x);
}

const Precision_t Vector2::Dot(const Vector2 &v) const
{
	return (x * v.x) + (y * v.y);
}

const Precision_t Vector2::Cross(const Vector2 &v) const
{
	return (x * v.y) - (y * v.x);
}

const Precision_t Vector2::Magnitude() const
{
	return std::sqrt(Dot(*this));
}

const Vector2 Vector2::Normal() const
{
	return *this / Magnitude();
}

const Precision_t Vector2::GetDistance(const Vector2 &v) const
{
	const Vector2 d = *this - v;
	return d.Magnitude();
}

bool AreEqual(Precision_t a, Precision_t b)
{
	return (a == b || std::fabs(a - b) <= 1e-12);
}
