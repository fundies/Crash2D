#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "vector2.hpp"
#include "collision.hpp"
#include "projection.hpp"

//!  A class representing an abstract geometric shape. */
class Shape
{
public:
	Shape();

	virtual const Vector2& GetCenter() const;

	virtual void SetPointCount(const unsigned &c);
	virtual void SetPoint(const unsigned &i, const Vector2 &p);

	virtual const unsigned GetPointCount() const;
	virtual const Vector2& GetPoint(const unsigned &i) const;
	virtual const Vector2 GetTransformedPoint(const unsigned &i) const;

	virtual void SetPos(const Vector2& _pos);

	virtual const Vector2& GetPos() const;

	virtual void Move(const Vector2 &o);

	virtual void Rotate(const Precision_t &a);
	virtual void SetRotation(const Precision_t &a);

	virtual const Precision_t& GetRotation() const;
	const std::vector<Vector2>& GetPoints() const;

protected:
	std::vector<Vector2> _points; /*!< The points this shape is composed of. */
	Precision_t _rotation; /*!< The rotation of this shape. */
	Vector2 _pos; /*!< The position of this shape. */
	Vector2 _center; /*!< The center of this shape. */
};

class Circle;
class Polygon;
class Line;

#endif
