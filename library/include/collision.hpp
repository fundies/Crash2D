#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "vector2.hpp"

//!  A class representing a collision between two shapes. */
class Collision
{
public:
	//! Constructs a collision with the given translation.
	/*!
		\param dI Whether the two shapes intersect.
		\param i Intersection points of the two shapes.
		\param aCb Whether shape A contains shape B.
		\param bCa Whether shape B contains shape A.
		\param t The minimum translation vector, returns 0,0 if there is no collision.
	*/
	Collision(bool dI, const std::vector<Vector2> i, bool aCb, bool bCa, const Vector2 t);

	//! Gets whether the two shapes intersect.
	/*!
		\return Whether the two shapes intersect.
	*/
	const bool Intersects() const;

	//! Gets the intersection points of the two shapes.
	/*!
		\return intersection points of the two shapes.
	*/
	const std::vector<Vector2>& GetIntersects() const;

	//! Gets whether shape A contains shape B.
	/*!
		\return Whether shape A contains shape B.
	*/
	const bool AcontainsB() const;

	//! Gets whether shape B contains shape A.
	/*!
		\return Whether shape B contains shape A.
	*/
	const bool BcontainsA() const;

	//! Gets the translation of this collision.
	/*!
		\return The translation of this collision.
	*/
	const Vector2& GetTranslation() const;

private:
	bool _doesIntersect; /*!< Whether the two shapes intersect. */
	const std::vector<Vector2> _intersects; /*!< Intersection points of the two shapes. */
	bool _aContainsb; /*!< Whether shape A contains shape B */
	bool _bContainsa; /*!< Whether shape B contains shape A */
	const Vector2 _translation; /*!< The minimum translation vector of this collision. */

};

#endif
