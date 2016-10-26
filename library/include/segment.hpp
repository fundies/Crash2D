#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"

//!  A class representing a line segment shape. */
class Segment : public Shape
{
public:
	//! Constructs a default line segment.
	/*!
		This line segment's points should be added through the base Shape class's interface.
		\sa Shape
	*/
	Segment();

	//! Constructs a line segment between the two points.
	/*!
		\param a The first point of the line segment.
		\param b The second point of the line segment.
	*/
	Segment(const Vector2 &a, const Vector2 &b);

	//! Sets the point at the given index to the new point.
	/*!
		\param i The index of the point. This should be 0 or 1 because a line segment only has two points.
		\param p The new point to replace the old point with.
	*/
	void SetPoint(const unsigned &i, const Vector2 &p);

	//! Gets the distance from this line segment to the given point and returns the result.
	/*!
		\param p The point to get the distance of this line segment to.
		\return The distance of this line segment to the given point.
	*/
	const Precision_t DistancePoint(const Vector2 &p, const Transform &t) const;

	//! Gets the signed distance from this line segment to the given point and returns the result.
	/*!
		\param p The point to get the signed distance of this line segment to.
		\return The signed distance of this line segment to the given point.
	*/
	const Precision_t SignedDistancePoint(const Vector2 &p, const Transform &t) const;

	//! Gets the length of the line segment and returns the result.
	/*!
		\return The length of the line segment.
	*/
	const Precision_t GetLength(const Transform &t) const;

	//! Gets the slope of the line segment and returns the result.
	/*!
		The slope is calculated as a ratio of rise over run. The function will return infinity or negative infinity for
		vertical lines because division by 0 is undefined.
		\return The slope of the line segment as a ratio.
	*/
	const Precision_t GetSlope(const Transform &t) const;

	const Precision_t GetSlope() const;

	//! Gets whether this line segment is perpendicular to the given line segment and returns the result.
	/*!
		Two lines are perpendicular if the opposite reciprocal of one line segment's slope is equal to the other line segment's slope. That
		is, if the negative of this line segment's run over rise ratio is equal to the given line segment's slope, then the lines are
		perpendicular and the function will return true. The function will otherwise return false.
		\param l The line segment to check if this line segment is perpendicular to.
		\return Whether this line segment is perpendicular to the given line segment.
	*/
	const bool IsPerpendicular(const Segment &l, const Transform &t1, const Transform &t2) const;

	//! Gets whether this line segment is parallel to the given line segment and returns the result.
	/*!
		This function will return true if the slope of this line segment is equal to the given line segment's slope.
		\param l The line segment to check if this line segment is parallel to.
		\return Whether this line segment is parallel to the given line segment.
	*/
	const bool IsParallel(const Segment &l, const Transform &t1, const Transform &t2) const;

	const bool IsParallel(const Segment &l) const;

	//! Gets whether this line segment contains the given point and returns the result.
	/*!
		\param p The point to check if this line segment contains.
		\return Whether this line segment contains the given point.
	*/
	const bool ContainsPoint(const Vector2 &p, const Transform &t) const;

	//! Gets whether this line segment intersects the given line segment and returns the result.
	/*!
		\param l THe line segment to check if this line segment intersects.
		\return Whether this line segment intersects the given line segment.
	*/
	const bool Intersects(const Segment &l, const Transform &t1, const Transform &t2) const;

	//! Gets the point of intersection between this line segment and the given line segment and returns the result.
	/*!
		\param l The line segment to find the intersection of this line segment.
		\return The point of intersection between this line segment and the given line segment.
	*/
	const Vector2 GetIntersect(const Segment &l, const Transform &t1, const Transform &t2) const;

	//! Gets the minimum translation vector between this line segment and the given line segment and returns the result.
	/*!
		\param l The line segment to get the minimum translation vector of this line segment.
		\return The minimum translation vector of this line segment with the given line segment.
	*/
	const Vector2 GetTranslation(const Segment &l, const Transform &t1, const Transform &t2) const;

	//! Gets the axis of this line segment.
	/*!
		The axis of the line segment is precalculated as the normal perpendicular to this line segment's normal.
		\return The axis of this line segment.
	*/
	const Axis& GetAxis() const;

private:
	void Recalc();
	Axis _axis; /*!< The axis of this circle. */
};

#endif // LINE_HPP
