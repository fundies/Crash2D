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

	//! Projects the circle onto the given axis and returns the projection.
	/*!
		\param a The axis to project the circle onto.
		\return The projection of the circle onto the axis.
	*/
	const Projection Project(const Axis &a) const;

	//! Checks if this circle collides with the given circle and returns the result.
	/*!
		Unlike the Contains() function, this function will also check if the given circle contains this circle.
		\param c The circle to check for collisions with.
		\return The collision result including the minimum translation vector.
		\sa Contains()
	*/
	const Collision GetCollision(const Circle &c) const;

	//! Checks if this circle collides with the given polygon and returns the result.
	/*!
		Unlike the Contains() function, this function will also check if the given polygon contains this circle.
		\param p The polygon to check for collisions with.
		\return The collision result including the minimum translation vector.
		\sa Contains()
	*/
	const Collision GetCollision(const Polygon &p) const;

	//! Gets the radius of the circle.
	/*!
		\return The circle of the radius.
	*/
	const Precision_t& GetRadius() const;

	//! Checks if the circles contains the given vector and returns the result.
	/*!
		\param p The vector to check for containment in this circle.
		\return The function returns true if the circle contains the vector, otherwise the function returns false.
	*/
	const bool Contains(const Vector2 &p) const;

	//! Checks if the circles contains the given polygon and returns the result.
	/*!
		This function does not check if the given polygon contains this circle, however. For that you should use the
		GetCollision() function.
		\param p The polygon to check for containment in this circle.
		\return The function returns true if the circle contains the polygon, otherwise the function returns false.
		\sa GetCollision()
	*/
	const bool Contains(const Polygon &p) const;

private:
	Precision_t _radius; /*!< The radius of this circle. */
};

#endif
