#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

//!  A class representing a circle shape. */
class Circle : public Shape
{
public:
	//! Constructs a circle with the given radius.
	/*!
		\param r The radius of the new circle.
	*/
	Circle(const Precision_t &r);

	//! Gets the radius of this circle.
	/*!
		\return The radius of this circle.
	*/
	const Precision_t& GetRadius() const;

	//! Projects the circle onto the given axis and returns the projection.
	/*!
		\param a The axis to project the circle onto.
		\return The projection of the circle onto the axis.
	*/
	const Projection Project(const Axis &a) const;

	//! Checks if this circle contains the given vector and returns the result.
	/*!
		\param v The vector to check for containment in this circle.
		\return Whether this circle contains the given vector.
	*/
	const bool Contains(const Vector2 &v) const;

	//! Checks if this circle contains the given segment and returns the result.
	/*!
		This function will not check if the given circle contains this segment, GetCollision() can be used for that.
		\param s The segment to check for containment in this circle.
		\return Whether this circle contains the given segment.
		\sa GetCollision()
	*/
	const bool Contains(const Segment &s) const;

	//! Checks if this circle contains the given circle and returns the result.
	/*!
		This function will not check if the given circle contains this circle, GetCollision() can be used for that.
		\param c The circle to check for containment in this circle.
		\return Whether this circle contains the given circle.
		\sa GetCollision()
	*/
	const bool Contains(const Circle &c) const;

	//! Checks if this circle contains the given polygon and returns the result.
	/*!
		This function will not check if the given polygon contains this circle, GetCollision() can be used for that.
		\param p The polygon to check for containment in this circle.
		\return Whether this circle contains the given polygon.
		\sa GetCollision()
	*/
	const bool Contains(const Polygon &p) const;

	//! Checks if this circle intersects the given segment and returns the result.
	/*!
		\param s The segment to check for intersection with this circle.
		\return Whether this circle intersects the given segment.
		\sa GetCollision()
	*/
	const bool Intersects(const Segment &s) const;

	//! Checks if this circle intersects the given circle and returns the result.
	/*!
		\param c The circle to check for intersection with this circle.
		\return Whether this circle intersects the given circle.
		\sa GetCollision()
	*/
	const bool Intersects(const Circle &c) const;

	//! Checks if this circle intersects the given polygon and returns the result.
	/*!
		\param p The polygon to check for intersection with this circle.
		\return Whether this circle intersects the given polygon.
		\sa GetCollision()
	*/
	const bool Intersects(const Polygon &p) const;

	//! Gets the intersection points of this circle and the given segment.
	/*!
		\param s A segment intersecting this circle.
		\return list of intersections between this circle and the given segment.
		\sa GetCollision()
	*/
	const std::vector<Vector2> GetIntersections(const Segment &s) const;

	//! Gets the intersection points of this circle and the given circle.
	/*!
		\param c A circle intersecting this circle.
		\return list of intersections between this circle and the given circle.
		\sa GetCollision()
	*/
	const std::vector<Vector2> GetIntersections(const Circle &c) const;

	//! Gets the intersection points of this circle and the given polygon.
	/*!
		\param p A polygon intersecting this circle.
		\return list of intersections between this circle and the given polygon.
		\sa GetCollision()
	*/
	const std::vector<Vector2> GetIntersections(const Polygon &p) const;

	//! Gets the minimum vector to be applied to the given segment's position
	//! in order to seperate it from this circle.
	/*!
		\param c A segment intersecting this circle.
		\return the minimum translation vector.
		\sa GetCollision()
	*/
	const Vector2 GetTranslation(const Segment &s) const;

	//! Gets the minimum vector to be applied to the given circle's position
	//! in order to seperate it from this circle.
	/*!
		\param c A circle intersecting this circle.
		\return the minimum translation vector.
		\sa GetCollision()
	*/
	const Vector2 GetTranslation(const Circle &c) const;

	//! Gets the minimum vector to be applied to the given polygon's position
	//! in order to seperate it from this circle.
	/*!
		\param p A polygon intersecting this circle.
		\return the minimum translation vector.
		\sa GetCollision()
	*/
	const Vector2 GetTranslation(const Polygon &p) const;

	//! Gets the collision of this circle with the given segment and returns the result.
	/*!
		\param s The segment to check for collision with this circle.
		\return The collision result including the minimum translation vector.
		\sa Contains()
	*/
	const Collision GetCollision(const Segment &s) const;

	//! Gets the collision of this circle with the given circle and returns the result.
	//! Unlike the Contains() function, this function will also check if the given circle contains this circle.
	/*!
		\param c The circle to check for collision with this circle.
		\return The collision result including the minimum translation vector.
		\sa Contains()
	*/
	const Collision GetCollision(const Circle &c) const;

	//! Gets the collision of this circle with the given polygon and returns the result.
	/*!
		Unlike the Contains() function, this function will also check if the given polygon contains this circle.
		\param p The polygon to check for collision with this circle.
		\return The collision result including the minimum translation vector.
		\sa Contains()
	*/
	const Collision GetCollision(const Polygon &p) const;

private:
	Precision_t _radius; /*!< The radius of this circle. */
};

#endif
