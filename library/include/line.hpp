#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"

//!  A class representing a line shape. */
class Line : public Shape
{
public:
	//! Constructs a default line.
	/*!
	*/
	Line();

	//! Constructs a line between the two points.
	/*!
		\param a The first point of the line.
		\param b The second point of the line.
	*/
	Line(const Vector2 &a, const Vector2 &b);

	//! Sets
	/*!
		\param i
		\param p
	*/
	void SetPoint(const unsigned &i, const Vector2 &p);

	//! Gets
	/*!
		\param p
		\return
	*/
	const Precision_t DistancePoint(const Vector2 &p) const;

	//! Gets
	/*!
		\param p
		\return
	*/
	const Precision_t SignedDistancePoint(const Vector2 &p) const;

	//! Gets the length of the line and returns the result.
	/*!
		\return The length of the line.
	*/
	const Precision_t& GetLength() const;

	//! Gets the slope of the line and returns the result.
	/*!
		The slope is calculated as a ratio of rise over run.
		\return The slope of the line as a ratio.
	*/
	const Precision_t& GetSlope() const;

	//! Gets whether this line is perpendicular to the given line and returns the result.
	/*!
		Two lines are perpendicular if the opposite reciprocal of one line's slope is equal to the other line's slope. That
		is, if the negative of this line's run over rise ratio is equal to the given line's slope, then the lines are
		perpendicular and the function will return true. The function will otherwise return false.
		\param l The line to check if this line is perpendicular to.
		\return Whether this line is perpendicular to the given line.
	*/
	const bool IsPerpendicular(const Line &l) const;

	//! Gets whether this line is parallel to the given line and returns the result.
	/*!
		This function will return true if the slope of this line is equal to the given line's slope.
		\param l The line to check if this line is parallel to.
		\return Whether this line is parallel to the given line.
	*/
	const bool IsParallel(const Line &l) const;

	//! Gets whether this line contains the given point and returns the result.
	/*!
		\param p The point to check if this line contains.
		\return Whether this line contains the given point.
	*/
	const bool ContainsPoint(const Vector2 &p) const;

	//! Gets whether this line intersects the given line and returns the result.
	/*!
		\param l THe line to check if this line intersects.
		\return Whether this line intersects the given line.
	*/
	const bool Intersects(const Line &l) const;

	//! Gets
	/*!
		\param l
		\return
	*/
	const Vector2 GetIntersect(const Line &l) const;

	//! Gets
	/*!
		\param l
		\return
	*/
	const Vector2 GetTranslation(const Line &l) const;

	//! Rotates this line by the given amount.
	/*!
		\param a The angle in radians.
	*/
	void Rotate(const Precision_t &a);

	//! Gets
	/*!
		\return
	*/
	const Axis& GetAxis() const;

private:
	void Recalc();

	Precision_t _slope; /*!< The slope of this line, that is, its rise over run. */
	Precision_t _length; /*!< The length of this line. */

	Axis _axis; /*!< The axis of this circle. */
};

#endif // LINE_HPP
