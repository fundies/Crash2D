#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "vector2.hpp"

//!  A class representing a 2D Transformation */
class Transform
{
public:
	//! Constructs a default transformation.
	/*!
		The transformations must be set manually.
	*/
	Transform();

	//! Constructs a transformation with a given scale, radius and translation
	/*!
		\param s The tranformation's scale.
		\param r The tranformation's rotation.
		\param t The tranformation's translation.
	*/
	Transform(const Precision_t &s, const Precision_t &r, const Vector2 &t);

	//! Gets the scale of this transformation.
	/*!
		\return The scale of this transformation.
	*/
	const Precision_t& GetScale() const;

	//! Sets the scale of this transformation.
	/*!
		\param s The new scale of the transformation.
	*/
	void SetScale(const Precision_t &s);

	//! Applies a value to the current scale of this transformation.
	/*!
		\param s The value to apply to the scale of the transformation.
	*/
	void Scale(const Precision_t &s);

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


protected:
	Precision_t _scale; /*!< The scale of the transformation. */
	Precision_t _rotation; /*!< The rotation of the transformation. */
	Vector2 _translation; /*!< The translation of the transformation. */
};

#endif
