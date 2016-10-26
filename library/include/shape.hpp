#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "vector2.hpp"
#include "collision.hpp"
//#include "projection.hpp"
//#include "transform.hpp"

class Circle;
class Polygon;
class Segment;
class Projection;
class Transform;

//!  A class representing an abstract geometric shape. */
class Shape
{
public:
	//! Constructs a default shape.
	/*!
		This shape's points must be added manually.
	*/
	Shape();

	//! Gets the center of this shape.
	/*!
		\return The center of this shape.
	*/
	virtual const Vector2& GetCenter() const;

	//! Sets the number of points in this shape.
	/*!
		\param c The number of points in this shape.
	*/
	virtual void SetPointCount(const unsigned &c);

	//! Sets the point of this shape at the given index to the new point.
	/*!
		\param i The index of the point.
		\param p The new point to replace the old point with.
	*/
	virtual void SetPoint(const unsigned &i, const Vector2 &p);

	//! Gets the number of points in this shape.
	/*!
		\return The number of points in this shape.
	*/
	virtual const unsigned GetPointCount() const;

	//! Gets the point of this shape at the given index.
	/*!
		\param i The index of the point.
		\return The point of this shape at the given index.
	*/
	virtual const Vector2& GetPoint(const unsigned &i) const;

	//! Gets the point of this shape at the given index using this shape's transformation.
	/*!
		\param t The trasformation applied.
		\param i The index of the point.
		\return The point of this shape at the given index using this shape's transformation.
	*/
	virtual const Vector2 GetTransformedPoint(const unsigned &i, const Transform &t) const;

	//! Gets the center of this shape at the given index using this shape's transformation.
	/*!
		\param t The trasformation applied.
		\return The point of this shape at the given index using this shape's transformation.
	*/
	virtual const Vector2 GetTransformedCenter(const Transform &t) const;

	//! Gets the points this shape is composed of.
	/*!
		\return The points this shape is composed of.
	*/
	const std::vector<Vector2>& GetPoints() const;

protected:
	std::vector<Vector2> _points; /*!< The points this shape is composed of. */
	Vector2 _center; /*!< The center of this shape. */
};

#endif
