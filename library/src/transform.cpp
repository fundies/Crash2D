#include "transform.hpp"

#include <cmath> //std::fmod

Transform::Transform()
	: _scale(1), _rotation(0), _translation(Vector2(0, 0))
{
}

Transform::Transform(const Precision_t &s, const Precision_t &r, const Vector2 &t)
	: _scale(s), _rotation(r), _translation(t)
{
}

const Precision_t& Transform::GetScale() const
{
	return _scale;
}

void Transform::SetScale(const Precision_t &s)
{
	_scale = s;
}

void Transform::Scale(const Precision_t &s)
{
	_scale += s;
}

const Precision_t& Transform::GetRotation() const
{
	return _rotation;
}

void Transform::SetRotation(const Precision_t &r)
{
	_rotation = r;

	_rotation = std::fmod(_rotation, 360.0);

	if (_rotation < 0)
		_rotation += 360;
}

void Transform::Rotate(const Precision_t &r)
{
	_rotation += r;

	_rotation = std::fmod(_rotation, 360.0);

	if (_rotation < 0)
		_rotation += 360;
}

const Vector2& Transform::GetTranslation() const
{
	return _translation;
}

void Transform::SetTranslation(const Vector2 &t)
{
	_translation = t;
}

void Transform::Translate(const Vector2 &t)
{
	_translation += t;
}
