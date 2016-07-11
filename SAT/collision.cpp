#include "collision.hpp"
#include "vector2.hpp"

Collision::Collision(Vector2 translation, bool touching)
{
	_touching = touching;
	_translation = translation;
}

bool Collision::IsTouching() const
{
	return _touching;
}

const Vector2& Collision::GetTranslation() const
{
	return _translation;
}
