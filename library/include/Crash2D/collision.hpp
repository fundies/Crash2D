#ifndef CRASH2D_COLLISION_HPP
#define CRASH2D_COLLISION_HPP

#include <Crash2D/vector2.hpp>

#include <algorithm>

namespace Crash2D
{
//!  A class representing a collision between two shapes. */
class Collision
{
public:
	//! Constructs an empty collision.
	/*!
	*/
	Collision();

	//! Constructs a collision with the given displacement.
	/*!
		\param dI Whether the two shapes intersect.
		\param i Intersection points of the two shapes.
		\param aCb Whether shape A contains shape B.
		\param bCa Whether shape B contains shape A.
		\param o Overlap of the two shapes
		\param t The minimum displacement vector, returns 0,0 if there is no collision.
	*/
	Collision(bool dI, const std::vector<Vector2> i, bool aCb, bool bCa, const Precision_t o, const Vector2 t);

	//! Gets whether the two shapes intersect.
	/*!
		\return Whether the two shapes intersect.
	*/
	const bool Overlaps() const;
	
	//! Gets the ammount of overlap between the two shapes.
	/*!
		\return Whether the two shapes intersect.
	*/
	const Precision_t GetOverlap() const;

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

	//! Gets the displacement of this collision.
	/*!
		\return The displacement of this collision.
	*/
	const Vector2& GetDisplacement() const;

	//! Negate Operator override,
	/*!
	*/
	const Collision operator - (void) const;

private:
	bool _doesOverlap; /*!< Whether the two shapes intersect. */
	std::vector<Vector2> _intersects; /*!< Intersection points of the two shapes. */
	bool _aContainsb; /*!< Whether shape A contains shape B */
	bool _bContainsa; /*!< Whether shape B contains shape A */
	Precision_t _overlap; /*!<Ammount of overlap between shape A and B. */
	Vector2 _displacement; /*!< The minimum displacement vector of this collision. */

};
}

#endif
