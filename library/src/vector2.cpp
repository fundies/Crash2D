#include "vector2.hpp"

#include <cmath>
#include <iostream>

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

const Precision_t Vector2::LengthSq() const
{
	return Dot(*this);
}

const Precision_t Vector2::Length() const
{
	return std::sqrt(LengthSq());
}

const Vector2 Vector2::Normal() const
{
	return *this / Length();
}

const Precision_t Vector2::GetDistance(const Vector2 &v) const
{
	const Vector2 d = *this - v;
	return d.Length();
}

bool AreEqual(Precision_t a, Precision_t b)
{
	//change 0.1 to real precision
	return (a == b || std::fabs(a - b) <= 0.1);
}
