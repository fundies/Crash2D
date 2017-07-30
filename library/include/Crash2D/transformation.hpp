#ifndef CRASH2D_TRANSFORMATION_HPP
#define CRASH2D_TRANSFORMATION_HPP

#include <Crash2D/vector2.hpp>

namespace Crash2D
{
//!  A class representing a 2D Transformation */
class Transformation
{
public:
	//! Constructs a default transformation.
	/*!
		The transformations must be set manually.
	*/
	Transformation();

	//! Constructs a transformation with a given scale, radius and translation
	/*!
		\param s The tranformation's scale.
		\param r The tranformation's rotation.
		\param t The tranformation's translation.
	*/
	Transformation(const Vector2 &s, const Precision_t &r, const Vector2 &t);

	//! Gets the scale of this transformation.
	/*!
		\return The scale of this transformation.
	*/
	const Vector2& GetScale() const;

	//! Sets the scale of this transformation.
	/*!
		\param s The new scale of the transformation.
	*/
	void SetScale(const Vector2 &s);

	//! Applies a value to the current scale of this transformation.
	/*!
		\param s The value to apply to the scale of the transformation.
	*/
	void Scale(const Vector2 &s);

	//! Gets the pivot point used for rotation.
	/*!
		\return The rotation of this transformation.
	*/
	const Vector2& GetPivot() const;

	//! Sets the pivot point used for rotation.
	/*!
		\param p The new pivot point used for rotation..
	*/
	void SetPivot(const Vector2 &p);

	//! Gets the rotation of this transformation.
	/*!
		\return The rotation of this transformation.
	*/
	const Precision_t& GetRotation() const;

	//! Sets the rotation of this transformation.
	/*!
		\param r The new rotation of the transformation.
	*/
	void SetRotation(const Precision_t &r);

	//! Applies a value to the current rotation of this transformation.
	/*!
		\param r The value to apply to the rotation of the transformation.
	*/
	void Rotate(const Precision_t &r);

	//! Gets the translation of this transformation.
	/*!
		\return The translation of this transformation.
	*/
	const Vector2& GetTranslation() const;

	//! Sets the translation of this transformation.
	/*!
		\param t The new translation of the transformation.
	*/
	void SetTranslation(const Vector2 &t);

	//! Applies a value to the current translation of this transformation.
	/*!
		\param t The value to apply to the translation of the transformation.
	*/
	void Translate(const Vector2 &t);

	//! Negate Operator override,
	/*!
	*/
	const Transformation operator - (void) const;


protected:
	Vector2 _scale; /*!< The scale of the transformation. */
	Precision_t _rotation; /*!< The rotation of the transformation. */
	Vector2 _translation; /*!< The translation of the transformation. */
	Vector2 _pivot; /*!< The pivot point used for rotation of the transformation. */
};
}

#endif
