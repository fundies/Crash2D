#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "vector2.hpp"
#include "collision.hpp"
#include "projection.hpp"

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
		\param i The index of the point.
		\return The point of this shape at the given index using this shape's transformation.
	*/
	virtual const Vector2 GetTransformedPoint(const unsigned &i) const;

	//! Sets the absolute position of this shape.
	/*!
		\param p The absolute position of this shape.
	*/
	virtual void SetPos(const Vector2& p);

	//! Gets the absolute position of this shape.
	/*!
		\return The absolute position of this shape.
	*/
	virtual const Vector2& GetPos() const;

	//! Moves this shape by the given offset relative to its current position.
	/*!
		\param o The offset to move this shape.
	*/
	virtual void Move(const Vector2 &o);

	//! Rotates this shape by the given angle relative to its current rotation.
	/*!
		\param a The relative angle to rotate this shape.
	*/
	virtual void Rotate(const Precision_t &a);

	//! Sets the absolute angle of rotation of this shape around its center.
	/*!
		\param a The absolute angle of rotation of this shape around its center.
	*/
	virtual void SetRotation(const Precision_t &a);

	//! Gets the absolute angle of rotation of this shape around its center.
	/*!
		\return The absolute angle of rotation of this shape around its center.
	*/
	virtual const Precision_t& GetRotation() const;

	//! Gets the points this shape is composed of.
	/*!
		\return The points this shape is composed of.
	*/
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
