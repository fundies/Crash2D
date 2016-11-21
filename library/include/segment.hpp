#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"

//!  A class representing a segment shape. */
class Segment : public Shape
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

	//! Sets the point at the given index to the new point.
	/*!
		\param i The index of the point. This should be 0 or 1 because a segment only has two points.
		\param p The new point to replace the old point with.
	*/
	void SetPoint(const unsigned &i, const Vector2 &p);

	//! Gets the distance from this segment to the given point and returns the result.
	/*!
		\param p The point to get the distance of this segment to.
		\return The distance of this segment to the given point.
	*/
	const Precision_t DistancePoint(const Vector2 &p) const;

	//! Gets the signed distance from this segment to the given point and returns the result.
	/*!
		\param p The point to get the signed distance of this segment to.
		\return The signed distance of this segment to the given point.
	*/
	const Precision_t SignedDistancePoint(const Vector2 &p) const;

	//! Gets the length of the segment and returns the result.
	/*!
		\return The length of the segment.
	*/
	const Precision_t& GetLength() const;

	//! Gets the slope of the segment and returns the result.
	/*!
		The slope is calculated as a ratio of rise over run. The function will return infinity or negative infinity for
		vertical lines because division by 0 is undefined.
		\return The slope of the segment as a ratio.
	*/
	const Precision_t& GetSlope() const;

	//! Gets whether this segment is perpendicular to the given segment and returns the result.
	/*!
		Two lines are perpendicular if the opposite reciprocal of one segment's slope is equal to the other segment's slope. That
		is, if the negative of this segment's run over rise ratio is equal to the given segment's slope, then the lines are
		perpendicular and the function will return true. The function will otherwise return false.
		\param l The segment to check if this segment is perpendicular to.
		\return Whether this segment is perpendicular to the given segment.
	*/
	const bool IsPerpendicular(const Segment &l) const;

	//! Gets whether this segment is parallel to the given segment and returns the result.
	/*!
		This function will return true if the slope of this segment is equal to the given segment's slope.
		\param l The segment to check if this segment is parallel to.
		\return Whether this segment is parallel to the given segment.
	*/
	const bool IsParallel(const Segment &l) const;

	//! Gets whether this segment contains the given point and returns the result.
	/*!
		\param p The point to check if this segment contains.
		\return Whether this segment contains the given point.
	*/
	const bool ContainsPoint(const Vector2 &p) const;

	//! Gets whether this segment intersects the given segment and returns the result.
	/*!
		\param l THe segment to check if this segment intersects.
		\return Whether this segment intersects the given segment.
	*/
	const bool Intersects(const Segment &l) const;

	//! Gets the point of intersection between this segment and the given segment and returns the result.
	/*!
		\param l The segment to find the intersection of this segment.
		\return The point of intersection between this segment and the given segment.
	*/
	const Vector2 GetIntersect(const Segment &l) const;

	//! Gets the minimum translation vector between this segment and the given segment and returns the result.
	/*!
		\param l The segment to get the minimum translation vector of this segment.
		\return The minimum translation vector of this segment with the given segment.
	*/
	const Vector2 GetTranslation(const Segment &l) const;

	//! Rotates this segment by the given angle.
	/*!
		\param a The angle to rotate this segment.
	*/
	void Rotate(const Precision_t &a);

	//! Gets the axis of this segment.
	/*!
		The axis of the segment is precalculated as the normal perpendicular to this segment's normal.
		\return The axis of this segment.
	*/
	const Axis& GetAxis() const;

private:
	void Recalc();

	Precision_t _slope; /*!< The slope of this segment, that is, its rise over run. */
	Precision_t _length; /*!< The length of this segment. */

	Axis _axis; /*!< The axis of this circle. */
};

#endif // LINE_HPP
