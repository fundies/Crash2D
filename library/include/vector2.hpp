#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <vector>

using Precision_t = double;
const Precision_t EPS = 1e-12;

bool AreEqual(Precision_t a, Precision_t b);

//!  A class representing a two-dimensional vector. */
class Vector2
{
public:
	Precision_t x; /*!< The x coordinate of this vector. */
	Precision_t y; /*!< The y coordinate of this vector. */

	//! Constructs a default two-dimensional vector whose coordinates are initialized to zero.
	/*!
	*/
	Vector2() : x(0), y(0) {}

	//! Constructs a two-dimensional vector.
	/*!
		\param x The x coordinate of the vector.
		\param y The y coordinate of the vector.
	*/
	Vector2(const Precision_t x, const Precision_t y) : x(x), y(y) {}

	const Vector2 Perpendicular() const;

	//! Calculates the dot product of this vector with the given vector and returns the result.
	/*!
		\param v The vector to compute the dot product of this vector.
		\return The dot product of this vector with the given vector.
	*/
	const Precision_t Dot(const Vector2 &v) const;

	//! Calculates the cross product of this vector with the given vector and returns the result.
	/*!
		\param v The vector to compute the cross product of this vector.
		\return The cross product of this vector with the given vector.
	*/
	const Precision_t Cross(const Vector2 &v) const;

	//! Calculates the squared length of this vector and returns the result.
	/*!
		\return The squared length of this vector.
	*/
	const Precision_t LengthSq() const;

	//! Calculates the length or magnitude of this vector and returns the result.
	/*!
		\return The length of this vector.
	*/
	const Precision_t Length() const;

	//! Calculates the distance between this vector and the given vector and returns the result.
	/*!
		\param v The vector to compute the distance of this vector.
		\return The distance between this vector and the given vector.
	*/
	const Precision_t GetDistance(const Vector2 &v) const;

	//! Calculates the normal of this vector and returns the result.
	/*!
		\return The normal of this vector.
	*/
	const Vector2 Normalize() const;

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
	inline const Vector2 operator - (void) const
	{
		return Vector2(-x, -y);
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

using Axis = Vector2; /**< An alias representing the axis of a line. */
using AxesVec = std::vector<Axis>; /**< An alias representing a structure that can hold a shape's axes. */

#endif
