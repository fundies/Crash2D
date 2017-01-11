#ifndef LINE_HPP
#define LINE_HPP

#include "shape_impl.hpp"

//!  A class representing a segment shape. */
class Segment : public ShapeImpl
{
public:
	//! Constructs a default segment.
	/*!
		This segment's points should be added through the base Shape class's interface.
		\sa Shape
	*/
	Segment();

	//! Constructs a segment between the two points.
	/*!
		\param a The first point of the segment.
		\param b The second point of the segment.
	*/
	Segment(const Vector2 &a, const Vector2 &b);

	//! Gets the distance from this segment to the given point and returns the result.
	/*!
		\param p The point to get the distance of this segment to.
		\return The distance of this segment to the given point.
	*/
	virtual const Precision_t DistancePoint(const Vector2 &p) const;

	//! Gets the signed distance from this segment to the given point and returns the result.
	/*!
		\param p The point to get the signed distance of this segment to.
		\return The signed distance of this segment to the given point.
	*/
	virtual const Precision_t SignedDistancePoint(const Vector2 &p) const;

	//! Gets the length of the segment and returns the result.
	/*!
		\return The length of the segment.
	*/
	virtual const Precision_t& GetLength() const;

	//! Gets the slope of the segment and returns the result.
	/*!
		The slope is calculated as a ratio of rise over run. The function will return infinity or negative infinity for
		vertical lines because division by 0 is undefined.
		\return The slope of the segment as a ratio.
	*/
	virtual const Precision_t& GetSlope() const;

	//! Gets whether this segment is perpendicular to the given segment and returns the result.
	/*!
		Two lines are perpendicular if the opposite reciprocal of one segment's slope is equal to the other segment's slope. That
		is, if the negative of this segment's run over rise ratio is equal to the given segment's slope, then the lines are
		perpendicular and the function will return true. The function will otherwise return false.
		\param s The segment to check if this segment is perpendicular to.
		\return Whether this segment is perpendicular to the given segment.
	*/
	virtual const bool IsPerpendicular(const Segment &s) const;

	//! Gets whether this segment is parallel to the given segment and returns the result.
	/*!
		This function will return true if the slope of this segment is equal to the given segment's slope.
		\param s The segment to check if this segment is parallel to.
		\return Whether this segment is parallel to the given segment.
	*/
	virtual const bool IsParallel(const Segment &s) const;

	//! Gets the axis of this segment.
	/*!
		The axis of the segment is precalculated as the normal perpendicular to this segment's normal.
		\return The axis of this segment.
	*/
	virtual const Axis& GetAxis() const;

	//! Calculates the nearest point on the line segment to the given point.
	/*!
		\param p The point given to be used in the calculation.
		\return The calculated point.
	*/
	virtual const Vector2 GetNearestPoint(const Vector2 &p) const;

	//! Calculates the nearest end point on the line segment to the given point.
	/*!
		\param p The point given to be used in the calculation.
		\return The calculated point.
	*/
	virtual const Vector2 NearestVertex(const Vector2 &p) const;

	//! Projects the line segment on the given axis.
	/*!
		\param a The axis to project the segment upon.
		\return The calculated projection.
	*/
	virtual const Projection Project(const Axis &a) const;

	//! Projects the shape onto the given axis and returns the projection.
	/*!
		\param s The shape to project.
		\param a The axis to project the circle onto.
		\return The projection of the circle onto the axis.
	*/
	virtual const Projection Project(const Shape &s, const Axis &a) const override;

	//! Checks if this segment contains the given vector and returns the result.
	/*!
		\param v The vector to check for containment in this segment.
		\return Whether this segment contains the given vector.
	*/
	virtual const bool Contains(const Vector2 &v) const;

	//! Checks if this segment contains the given segment and returns the result.
	/*!
		This function will not check if the given circle contains this segment, GetCollision() can be used for that.
		\param c The circle to check for containment in this segment.
		\return Whether this segment contains the given circle.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Segment &s) const override;

	//! Checks if this segment contains the given circle and returns the result.
	/*!
		\param s The segment to check for containment in this segment.
		\return Whether this segment contains the given segment.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Circle &c) const override;

	//! Checks if this segment contains the given polygon and returns the result.
	/*!
		This function will not check if the given polygon contains this segment, GetCollision() can be used for that.
		\param p The polygon to check for containment in this segment.
		\return Whether this segment contains the given polygon.
		\sa GetCollision()
	*/
	virtual const bool Contains(const Polygon &p) const override;

	//! Checks if this segment intersects the given segment and returns the result.
	/*!
		\param s The segment to check for intersection with this segment.
		\return Whether this segment intersects the given segment.
		\sa GetCollision()
	*/
	virtual const bool Overlaps(const Segment &s) const override;

	//! Checks if this segment intersects the given circle and returns the result.
	/*!
		\param c The circle to check for intersection with this segment.
		\return Whether this segment intersects the given circle.
		\sa GetCollision()
	*/
	virtual const bool Overlaps(const Circle &c) const override;

	//! Checks if this segment intersects the given polygon and returns the result.
	/*!
		\param p The polygon to check for intersection with this segment.
		\return Whether this segment intersects the given polygon.
		\sa GetCollision()
	*/
	virtual const bool Overlaps(const Polygon &p) const override;

	//! Gets the intersection points of this segment and the given segment.
	/*!
		\param s A segment intersecting this segment.
		\return list of intersections between this segment and the given segment.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersects(const Segment &s) const override;

	//! Gets the intersection points of this segment and the given circle.
	/*!
		\param c A circle intersecting this segment.
		\return list of intersections between this segment and the given circle.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersects(const Circle &c) const override;

	//! Gets the intersection points of this segment and the given polygon.
	/*!
		\param p A polygon intersecting this segment.
		\return list of intersections between this segment and the given polygon.
		\sa GetCollision()
	*/
	virtual const std::vector<Vector2> GetIntersects(const Polygon &p) const override;

	//! Gets the minimum vector to be applied to the given segment's position
	//! in order to seperate it from this segment.
	/*!
		\param c A segment intersecting this segment.
		\return the minimum displacement vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetDisplacement(const Segment &s) const override;

	//! Gets the minimum vector to be applied to the given circle's position
	//! in order to seperate it from this segment.
	/*!
		\param c A circle intersecting this segment.
		\return the minimum displacement vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetDisplacement(const Circle &c) const override;

	//! Gets the minimum vector to be applied to the given polygon's position
	//! in order to seperate it from this segment.
	/*!
		\param p A polygon intersecting this segment.
		\return the minimum displacement vector.
		\sa GetCollision()
	*/
	virtual const Vector2 GetDisplacement(const Polygon &p) const override;

	//! Gets the collision of this segment with the given shape and returns the result.
	/*!
		\param s The shape to check for collision with this segment.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Shape &s) const override;

	//! Gets the collision of this segment with the given segment and returns the result.
	/*!
		\param s The segment to check for collision with this segment.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Segment &s) const override;

	//! Gets the collision of this segment with the given circle and returns the result.
	//! Unlike the Contains() function, this function will also check if the given circle contains this segment.
	/*!
		\param c The circle to check for collision with this segment.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Circle &c) const override;

	//! Gets the collision of this segment with the given polygon and returns the result.
	/*!
		Unlike the Contains() function, this function will also check if the given polygon contains this segment.
		\param p The polygon to check for collision with this segment.
		\return The collision result including the minimum displacement vector.
		\sa Contains()
	*/
	virtual const Collision GetCollision(const Polygon &p) const override;

	//! Method required to be called after updating the geometry of a shape.
	/*!
	*/
	virtual void ReCalc() override;

protected:

	Precision_t _slope; /*!< The slope of this segment, that is, its rise over run. */
	Precision_t _length; /*!< The length of this segment. */
	Axis _axis; /*!< The axis of this circle. */
};

#endif // LINE_HPP
