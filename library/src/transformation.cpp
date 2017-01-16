#include "transformation.hpp"

#include <cmath> //std::fmod

Transformation::Transformation()
	: _scale(1), _rotation(0), _translation(Vector2(0, 0))
{
}

Transformation::Transformation(const Precision_t &s, const Precision_t &r, const Vector2 &t)
	: _scale(s), _rotation(r), _translation(t)
{
}

const Precision_t& Transformation::GetScale() const
{
	return _scale;
}

void Transformation::SetScale(const Precision_t &s)
{
	_scale = s;
}

void Transformation::Scale(const Precision_t &s)
{
	_scale += s;
}

const Vector2& Transformation::GetPivot() const
{
	return _pivot;
}

void Transformation::SetPivot(const Vector2 &p)
{
	_pivot = p;
}

const Precision_t& Transformation::GetRotation() const
{
	return _rotation;
}

void Transformation::SetRotation(const Precision_t &r)
{
	_rotation = r;

	_rotation = std::fmod(_rotation, 360.0);

	if (_rotation < 0)
		_rotation += 360;
}

void Transformation::Rotate(const Precision_t &r)
{
	_rotation += r;

	_rotation = std::fmod(_rotation, 360.0);

	if (_rotation < 0)
		_rotation += 360;
}

const Vector2& Transformation::GetTranslation() const
{
	return _translation;
}

void Transformation::SetTranslation(const Vector2 &t)
{
	_translation = t;
}

void Transformation::Translate(const Vector2 &t)
{
	_translation += t;
}
