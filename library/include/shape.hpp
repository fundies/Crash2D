#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "vector2.hpp"
#include "collision.hpp"
#include "projection.hpp"

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
	std::vector<Vector2> _points;
	Precision_t _rotation;
	Vector2 _pos;
	Vector2 _center;
};

class Circle;
class Polygon;
class Line;

#endif
