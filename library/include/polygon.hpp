#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "shape.hpp"

//!  A class representing an n-sided polygon shape. */
class Polygon : public Shape
{
public:
	//! Constructs a default polygon.
	/*!
		This polygon's points should be added through the base Shape class's interface.
		\sa Shape
	*/
	Polygon();

	void ReCalc();

	//! Projects this polygon onto the given axis and returns the result.
	/*!
		\param a The axis to project this polygon onto.
		\return The projection of this polygon onto the given axis.
	*/
	const Projection Project(const Axis &a) const;

	//! Gets the collision of this polygon with the given polygon and returns the result.
	/*!
		Unlike the Contains() function, this function will also check if the given polygon contains this polygon.
		\param p The polygon to check for collision with this polygon.
		\return The collision result including the minimum translation vector.
		\sa Contains()
	*/
	const Collision GetCollision(const Polygon &p) const;

	//! Gets the collision of this polygon with the given circle and returns the result.
	/*!
		Unlike the Contains() function, this function will also check if the given circle contains this polygon.
		\param c The circle to check for collision with this polygon.
		\return The collision result including the minimum translation vector.
		\sa Contains()
	*/
	const Collision GetCollision(const Circle &c) const;

	//! Checks if this polygon contains the given vector and returns the result.
	/*!
		\param v The vector to check for containment in this polygon.
		\return Whether this polygon contains the given vector.
	*/
	const bool Contains(const Vector2 &v) const;

	//! Checks if this polygon contains the given polygon and returns the result.
	/*!
		This function will not check if the given polygon contains this polygon, GetCollision() can be used for that.
		\param p The polygon to check for containment in this polygon.
		\return Whether this polygon contains the given polygon.
		\sa GetCollision()
	*/
	const bool Contains(const Polygon &p) const;

	//! Checks if this polygon contains the given circle and returns the result.
	/*!
		This function will not check if the given circle contains this polygon, GetCollision() can be used for that.
		\param c The circle to check for containment in this polygon.
		\return Whether this polygon contains the given circle.
		\sa GetCollision()
	*/
	const bool Contains(const Circle &c) const;

	//! Gets the axes of this polygon's sides.
	/*!
		The axes of the sides is precalculated as the normal perpendicular to each side's normal.
		\return The axes of this polygon's sides.
	*/
	const AxesVec& GetAxes() const;

	//! Gets the sides this polygon is composed of.
	/*!
		The number of sides of a polygon will always be one less than the number of points.
		\return The sides this polygon is composed of.
	*/
	const std::vector<Segment>& GetSides() const;

	//! Gets the neareset vertex of this polygon to the given point and returns the result.
	/*!
		\param p The point to get the nearest vertex of this polygon.
		\return The nearest vertex of this polygon to the given point.
	*/
	const Vector2 NearestVertex(const Vector2 &point) const;

private:
	const bool TriangleContains(const Vector2 &p, const Vector2 &a, const Vector2 &b, const Vector2 &c) const;

	AxesVec _axes; /*!< The axes of this polygon. */
	std::vector<Segment> _side; /*!< The side of this polygon. */
};

#endif
