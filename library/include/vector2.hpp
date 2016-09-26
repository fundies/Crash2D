#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <vector>

using Precision_t = double;

bool AreEqual(Precision_t a, Precision_t b);

class Vector2
{
public:
	Precision_t x;
	Precision_t y;

	Vector2() : x(0), y(0) {}
	Vector2(const Precision_t x, const Precision_t y) : x(x), y(y) {}

	const Vector2 Perpendicular() const;
	const Precision_t Dot(const Vector2 &v) const;
	const Precision_t Cross(const Vector2 &v) const;
	const Precision_t Magnitude() const;
	const Precision_t GetDistance(const Vector2 &v) const;
	const Vector2 Normal() const;

	inline Vector2 & operator = (const Vector2 & v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	inline Vector2 & operator = (const Precision_t & f)
	{
		x = f;
		y = f;
		return *this;
	}
	inline Vector2 & operator - (void)
	{
		x = -x;
		y = -y;
		return *this;
	}
	inline bool operator == (const Vector2 & v) const
	{
		return (x == v.x) && (y == v.y);
	}
	inline bool operator != (const Vector2 & v) const
	{
		return (x != v.x) || (y != v.y);
	}

	//VECTOR2 TO VECTOR2 OPERATIONS
	inline const Vector2 operator + (const Vector2 & v) const
	{
		return Vector2(x + v.x, y + v.y);
	}
	inline const Vector2 operator - (const Vector2 & v) const
	{
		return Vector2(x - v.x, y - v.y);
	}
	inline const Vector2 operator * (const Vector2 & v) const
	{
		return Vector2(x * v.x, y * v.y);
	}
	inline const Vector2 operator / (const Vector2 & v) const
	{
		return Vector2(x / v.x, y / v.y);
	}

	//VECTOR2 TO THIS OPERATIONS
	inline Vector2 & operator += (const Vector2 & v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	inline Vector2 & operator -= (const Vector2 & v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	inline Vector2 & operator *= (const Vector2 & v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}
	inline Vector2 & operator /= (const Vector2 & v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	//SCALER TO VECTOR2 OPERATIONS
	inline const Vector2 operator + (Precision_t v) const
	{
		return Vector2(x + v, y + v);
	}
	inline const Vector2 operator - (Precision_t v) const
	{
		return Vector2(x - v, y - v);
	}
	inline const Vector2 operator * (Precision_t v) const
	{
		return Vector2(x * v, y * v);
	}
	inline const Vector2 operator / (Precision_t v) const
	{
		return Vector2(x / v, y / v);
	}

	//SCALER TO THIS OPERATIONS
	inline Vector2 & operator += (Precision_t v)
	{
		x += v;
		y += v;
		return *this;
	}
	inline Vector2 & operator -= (Precision_t v)
	{
		x -= v;
		y -= v;
		return *this;
	}
	inline Vector2 & operator *= (Precision_t v)
	{
		x *= v;
		y *= v;
		return *this;
	}
	inline Vector2 & operator /= (Precision_t v)
	{
		x /= v;
		y /= v;
		return *this;
	}
};

using Axis = Vector2;
using AxesVec = std::vector<Axis>;

#endif
