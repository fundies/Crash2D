#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "shape_impl.hpp"

//!  A class representing an n-sided polygon shape. */
class Polygon : public ShapeImpl
{
public:
	//! Constructs a default polygon.
	/*!
		This polygon's points should be added through the base Shape class's interface.
		\sa Shape
	*/
	Polygon();

	//! Gets the axes of this polygon's sides.
	/*!
		The axes of the sides is precalculated as the normal perpendicular to each side's normal.
		\return The axes of this polygon's sides.
	*/
	virtual const AxesVec& GetAxes() const;

	//! Gets the sides this polygon is composed of.
	/*!
		The number of sides of a polygon will always be one less than the number of points.
		\return The sides this polygon is composed of.
	*/
	virtual const std::vector<Segment>& GetSides() const;

	//! Gets the neareset vertex of this polygon to the given point and returns the result.
	/*!
		\param p The point to get the nearest vertex of this polygon.
		\return The nearest vertex of this polygon to the given point.
	*/
	virtual const Vector2 NearestVertex(const Vector2 &p) const;

	//! Projects this polygon onto the given axis and returns the result.
	/*!
		\param a The axis to project this polygon onto.
		\return The projection of this polygon onto the given axis.
	*/
	virtual const Projection Project(const Axis &a) const override;

	//! Projects the shape onto the given axis and returns the projection.
	/*!
		\param s The shape to project.
		\param a The axis to project the circle onto.
		\return The projection of the circle onto the axis.
	*/
	virtual const Projection Project(const Shape &s, const Axis &a) const override;

	//! Checks if this polygon contains the given vector and returns the result.
	/*!
		\param v The vector to check for containment in this polygon.
		\return Whether this polygon contains the given vector.
	*/
	virtual const bool Contains(const Vector2 &v) const override;

	//! Checks if this shape contains the given shape and returns the result.
	/*!
		\param s The shape to check for containment in this shape.
		\return Whether this shape contains the given vector.
	*/
	virtual const bool Contains(const Shape &s) const override;

	//! Checks if this polygon contains the given segment and returns the result.
	/*!
		This function will not check if the given circle contains this polygon, GetCollision() can be used for that.
		\param c The circle to check for containment in this polygon.
		\return Whether this polygon contains the given circle.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Segment &s) const override;

	//! Checks if this polygon contains the given circle and returns the result.
	/*!
		\param s The segment to check for containment in this polygon.
		\return Whether this polygon contains the given segment.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Circle &c) const override;

	//! Checks if this polygon contains the given polygon and returns the result.
	/*!
		This function will not check if the given polygon contains this polygon, GetCollision() can be used for that.
		\param p The polygon to check for containment in this polygon.
		\return Whether this polygon contains the given polygon.
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

	//! Checks if this polygon intersects the given segment and returns the result.
	/*!
		\param s The segment to check for intersection with this polygon.
		\return Whether this polygon intersects the given segment.
		\sa GetCollision()
	*/
	virtual const bool Overlaps(const Segment &s) const override;

	//! Checks if this polygon intersects the given circle and returns the result.
	/*!
		\param c The circle to check for intersection with this polygon.
		\return Whether this polygon intersects the given circle.
		\sa GetCollision()
	*/
	virtual const bool Overlaps(const Circle &c) const override;

	//! Checks if this polygon intersects the given polygon and returns the result.
	/*!
		\param p The polygon to check for intersection with this polygon.
		\return Whether this polygon intersects the given polygon.
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

	//! Gets the intersection points of this polygon and the given segment.
	/*!
		\param s A segment intersecting this polygon.
		\return list of intersections between this polygon and the given segment.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersects(const Segment &s) const override;

	//! Gets the intersection points of this polygon and the given circle.
	/*!
		\param c A circle intersecting this polygon.
		\return list of intersections between this polygon and the given circle.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersects(const Circle &c) const override;

	//! Gets the intersection points of this polygon and the given polygon.
	/*!
		\param p A polygon intersecting this polygon.
		\return list of intersections between this polygon and the given polygon.
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
	//! in order to seperate it from this polygon.
	/*!
		\param c A segment intersecting this polygon.
		\return the minimum displacement vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetDisplacement(const Segment &s) const override;

	//! Gets the minimum vector to be applied to the given circle's position
	//! in order to seperate it from this polygon.
	/*!
		\param c A circle intersecting this polygon.
		\return the minimum displacement vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetDisplacement(const Circle &c) const override;

	//! Gets the minimum vector to be applied to the given polygon's position
	//! in order to seperate it from this polygon.
	/*!
		\param p A polygon intersecting this polygon.
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

	//! Gets the collision of this polygon with the given segment and returns the result.
	/*!
		\param s The segment to check for collision with this polygon.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Segment &s) const override;

	//! Gets the collision of this polygon with the given circle and returns the result.
	//! Unlike the Contains() function, this function will also check if the given circle contains this polygon.
	/*!
		\param c The circle to check for collision with this polygon.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Circle &c) const override;

	//! Gets the collision of this polygon with the given polygon and returns the result.
	/*!
		Unlike the Contains() function, this function will also check if the given polygon contains this polygon.
		\param p The polygon to check for collision with this polygon.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Polygon &p) const override;

	//! Applies a transformation to this shape..
	/*!
		\param t The transformation to be applied.
	*/
	virtual void Transform(const Transformation &t) override;

	//! Method required to be called after updating the geometry of a shape.
	/*!
	*/
	virtual void ReCalc() override;

protected:
	//! Checks if triangle "abc" contains the point "p".
	/*!
		\param p The point to check for containment within the triangle.
		\param a The first point on the triangle.
		\param b The second point on the triangle.
		\param c The third point on the triangle.
	*/
	const bool TriangleContains(const Vector2 &p, const Vector2 &a, const Vector2 &b, const Vector2 &c) const;

	AxesVec _axes; /*!< The axes of this polygon. */
	std::vector<Segment> _side; /*!< The sides of this polygon. */
};

#endif
