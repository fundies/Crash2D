#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "vector2.hpp"

//!  A class representing a collision between two shapes. */
class Collision
{
public:
	//! Constructs a collision with the given translation.
	/*!
		\param t The minimum translation vector, should be 0 if there is no collision.
		\param v Whether this collision is touching.
		\param c Whether this collision is contained.
	*/
	Collision(const Vector2 &t, const bool &v, const bool c);

	//! Gets whether this collision is touching.
	/*!
		\return Whether this collision is touching.
	*/
	bool IsTouching() const;

	//! Gets whether this collision is contained.
	/*!
		\return Whether this collision is contained.
	*/
	bool IsContained() const;

	//! Gets the translation of this collision.
	/*!
		\return The translation of this collision.
	*/
	const Vector2& GetTranslation() const;

private:
	Vector2 _translation; /*!< The minimum translation vector of this collision. */
	bool _touching; /*!< Whether this collision is touching. */
	bool _contained; /*!< Whether this collision is contained. */

};

#endif
