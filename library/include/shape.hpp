#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "vector2.hpp"
//#include "collision.hpp"
//#include "projection.hpp"

//class Vector2;
class Projection;
class Collision;
class Circle;
class Polygon;
class Segment;

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

	//! Projects the circle onto the given axis and returns the projection.
	/*!
		\param a The axis to project the circle onto.
		\return The projection of the circle onto the axis.
	*/
	virtual const Projection Project(const Axis &a) const;

	//! Checks if this shape contains the given vector and returns the result.
	/*!
		\param v The vector to check for containment in this shape.
		\return Whether this shape contains the given vector.
	*/
	virtual const bool Contains(const Vector2 &v) const;

	//! Checks if this shape contains the given segment and returns the result.
	/*!
		This function will not check if the given circle contains this segment, GetCollision() can be used for that.
		\param s The segment to check for containment in this shape.
		\return Whether this shape contains the given segment.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Segment &s) const;

	//! Checks if this shape contains the given circle and returns the result.
	/*!
		This function will not check if the given circle contains this shape, GetCollision() can be used for that.
		\param c The circle to check for containment in this shape.
		\return Whether this shape contains the given circle.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Circle &c) const;

	//! Checks if this shape contains the given polygon and returns the result.
	/*!
		This function will not check if the given polygon contains this shape, GetCollision() can be used for that.
		\param p The polygon to check for containment in this shape.
		\return Whether this shape contains the given polygon.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Polygon &p) const;

	//! Checks if this shape intersects the given segment and returns the result.
	/*!
		\param s The segment to check for intersection with this shape.
		\return Whether this shape intersects the given segment.
		\sa GetCollision()
	*/
	virtual const bool Intersects(const Segment &s) const;

	//! Checks if this shape intersects the given circle and returns the result.
	/*!
		\param c The circle to check for intersection with this shape.
		\return Whether this shape intersects the given circle.
		\sa GetCollision()
	*/
	virtual const bool Intersects(const Circle &c) const;

	//! Checks if this shape intersects the given polygon and returns the result.
	/*!
		\param p The polygon to check for intersection with this shape.
		\return Whether this shape intersects the given polygon.
		\sa GetCollision()
	*/
	virtual const bool Intersects(const Polygon &p) const;

	//! Gets the intersection points of this shape and the given segment.
	/*!
		\param s A segment intersecting this shape.
		\return list of intersections between this shape and the given segment.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersections(const Segment &s) const;

	//! Gets the intersection points of this shape and the given circle.
	/*!
		\param c A circle intersecting this shape.
		\return list of intersections between this shape and the given circle.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersections(const Circle &c) const;

	//! Gets the intersection points of this shape and the given polygon.
	/*!
		\param p A polygon intersecting this shape.
		\return list of intersections between this shape and the given polygon.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersections(const Polygon &p) const;

	//! Gets the minimum vector to be applied to the given segment's position
	//! in order to seperate it from this shape.
	/*!
		\param c A segment intersecting this shape.
		\return the minimum translation vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetTranslation(const Segment &s) const;

	//! Gets the minimum vector to be applied to the given circle's position
	//! in order to seperate it from this shape.
	/*!
		\param c A circle intersecting this shape.
		\return the minimum translation vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetTranslation(const Circle &c) const;

	//! Gets the minimum vector to be applied to the given polygon's position
	//! in order to seperate it from this shape.
	/*!
		\param p A polygon intersecting this shape.
		\return the minimum translation vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetTranslation(const Polygon &p) const;

	//! Gets the collision of this shape with the given segment and returns the result.
	/*!
		\param s The segment to check for collision with this shape.
		\return The collision result including the minimum translation vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Segment &s) const;

	//! Gets the collision of this shape with the given circle and returns the result.
	//! Unlike the Contains() function, this function will also check if the given circle contains this shape.
	/*!
		\param c The circle to check for collision with this shape.
		\return The collision result including the minimum translation vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Circle &c) const;

	//! Gets the collision of this shape with the given polygon and returns the result.
	/*!
		Unlike the Contains() function, this function will also check if the given polygon contains this shape.
		\param p The polygon to check for collision with this shape.
		\return The collision result including the minimum translation vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Polygon &p) const;

protected:
	std::vector<Vector2> _points; /*!< The points this shape is composed of. */
	Precision_t _rotation; /*!< The rotation of this shape. */
	Vector2 _pos; /*!< The position of this shape. */
	Vector2 _center; /*!< The center of this shape. */
};

#endif
