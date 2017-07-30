#ifndef CRASH2D_CIRCLE_HPP
#define CRASH2D_CIRCLE_HPP

#include <Crash2D/shape_impl.hpp>

namespace Crash2D
{

//!  A class representing a circle shape. */
class Circle : public ShapeImpl
{
public:
	//! Constructs a circle with radius 0.
	/*!
	*/
	Circle();

	//! Constructs a circle with the given radius.
	/*!
		\param c The center of the new circle.
		\param r The radius of the new circle.
	*/
	Circle(const Vector2 c, const Precision_t r);

	//! Sets the radius of this circle.
	/*!
	*/
	virtual void SetRadius(const Precision_t r);

	//! Gets the radius of this circle.
	/*!
		\return The radius of this circle.
	*/
	virtual const Precision_t& GetRadius() const;

	//! Projects the circle onto the given axis and returns the projection.
	/*!
		\param a The axis to project the circle onto.
		\return The projection of the circle onto the axis.
	*/
	virtual const Projection Project(const Axis &a) const override;

	//! Projects the shape onto the given axis and returns the projection.
	/*!
		\param s The shape to project.
		\param a The axis to project the circle onto.
		\return The projection of the circle onto the axis.
	*/
	virtual const Projection Project(const Shape &s, const Axis &a) const override;

	//! Checks if this circle contains the given vector and returns the result.
	/*!
		\param v The vector to check for containment in this circle.
		\return Whether this circle contains the given vector.
	*/
	virtual const bool Contains(const Vector2 &v) const override;

	//! Checks if this shape contains the given shape and returns the result.
	/*!
		\param s The shape to check for containment in this shape.
		\return Whether this shape contains the given vector.
	*/
	virtual const bool Contains(const Shape &s) const override;

	//! Checks if this circle contains the given segment and returns the result.
	/*!
		This function will not check if the given circle contains this segment, GetCollision() can be used for that.
		\param s The segment to check for containment in this circle.
		\return Whether this circle contains the given segment.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Segment &s) const override;

	//! Checks if this circle contains the given circle and returns the result.
	/*!
		This function will not check if the given circle contains this circle, GetCollision() can be used for that.
		\param c The circle to check for containment in this circle.
		\return Whether this circle contains the given circle.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Circle &c) const override;

	//! Checks if this circle contains the given polygon and returns the result.
	/*!
		This function will not check if the given polygon contains this circle, GetCollision() can be used for that.
		\param p The polygon to check for containment in this circle.
		\return Whether this circle contains the given polygon.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Polygon &p) const override;

	//! Checks if this shape is contained inside the given segment and returns the result.
	/*!
		\param s The shape to check if this shape is contained inside.
		\return Whether this shape contains the given segment.
	*/
	virtual const bool IsInside(const Shape &s) const override;

	//! Checks if this shape is contained inside the given segment and returns the result.
	/*!
		\param s The segment to check if this shape is contained inside.
		\return Whether this shape contains the given segment.
	*/
	virtual const bool IsInside(const Segment &s) const override;

	//! Checks if this shape is contained inside the given segment and returns the result.
	/*!
		\param c The circle to check if this shape is contained inside.
		\return Whether this shape contains the given segment.
	*/
	virtual const bool IsInside(const Circle &c) const override;

	//! Checks if this shape is contained inside the given segment and returns the result.
	/*!
		\param p The polygon to check if this shape is contained inside.
		\return Whether this shape contains the given segment.
	*/
	virtual const bool IsInside(const Polygon &p) const override;

	//! Checks if this shape intersects the given shape and returns the result.
	/*!
		\param s The shape to check for intersection with this shape.
		\return Whether this shape intersects the given segment.
		\sa GetCollision()
	*/
	virtual const bool Overlaps(const Shape &s) const override;

	//! Checks if this circle intersects the given segment and returns the result.
	/*!
		\param s The segment to check for intersection with this circle.
		\return Whether this circle intersects the given segment.
		\sa GetCollision()
	*/
	virtual const bool Overlaps(const Segment &s) const override;

	//! Checks if this circle intersects the given circle and returns the result.
	/*!
		\param c The circle to check for intersection with this circle.
		\return Whether this circle intersects the given circle.
		\sa GetCollision()
	*/
	virtual const bool Overlaps(const Circle &c) const override;

	//! Checks if this circle intersects the given polygon and returns the result.
	/*!
		\param p The polygon to check for intersection with this circle.
		\return Whether this circle intersects the given polygon.
		\sa GetCollision()
	*/
	virtual const bool Overlaps(const Polygon &p) const override;

	//! Gets the intersection points of this shape and the given shape.
	/*!
		\param s A segment intersecting this shape.
		\return list of intersections between this shape and the given segment.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersects(const Shape &s) const override;

	//! Gets the intersection points of this circle and the given segment.
	/*!
		\param s A segment intersecting this circle.
		\return list of intersections between this circle and the given segment.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersects(const Segment &s) const override;

	//! Gets the intersection points of this circle and the given circle.
	/*!
		\param c A circle intersecting this circle.
		\return list of intersections between this circle and the given circle.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersects(const Circle &c) const override;

	//! Gets the intersection points of this circle and the given polygon.
	/*!
		\param p A polygon intersecting this circle.
		\return list of intersections between this circle and the given polygon.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersects(const Polygon &p) const override;

	//! Gets the minimum vector to be applied to the given shape's position
	//! in order to seperate it from this shape.
	/*!
		\param c A segment intersecting this shape.
		\return the minimum displacement vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetDisplacement(const Shape &s) const override;

	//! Gets the minimum vector to be applied to the given segment's position
	//! in order to seperate it from this circle.
	/*!
		\param c A segment intersecting this circle.
		\return the minimum displacement vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetDisplacement(const Segment &s) const override;

	//! Gets the minimum vector to be applied to the given circle's position
	//! in order to seperate it from this circle.
	/*!
		\param c A circle intersecting this circle.
		\return the minimum displacement vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetDisplacement(const Circle &c) const override;

	//! Gets the minimum vector to be applied to the given polygon's position
	//! in order to seperate it from this circle.
	/*!
		\param p A polygon intersecting this circle.
		\return the minimum displacement vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetDisplacement(const Polygon &p) const override;

	//! Gets the collision of this circle with the given shape and returns the result.
	/*!
		\param s The shape to check for collision with this segment.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Shape &s) const override;

	//! Gets the collision of this circle with the given segment and returns the result.
	/*!
		\param s The segment to check for collision with this circle.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Segment &s) const override;

	//! Gets the collision of this circle with the given circle and returns the result.
	//! Unlike the Contains() function, this function will also check if the given circle contains this circle.
	/*!
		\param c The circle to check for collision with this circle.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Circle &c) const override;

	//! Gets the collision of this circle with the given polygon and returns the result.
	/*!
		Unlike the Contains() function, this function will also check if the given polygon contains this circle.
		\param p The polygon to check for collision with this circle.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Polygon &p) const override;

	//! Applies a transformation to this shape..
	/*!
		\param t The transformation to be applied.
	*/
	virtual void Transform(const Transformation &t) override;

	//! Clone Method.
	/*!
	*/
	virtual Shape* Clone() override;

protected:

	Precision_t _radius; /*!< The radius of this circle. */
};
}
#endif
