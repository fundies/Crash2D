#include "collision.hpp"
#include "vector2.hpp"

Collision::Collision(Vector2 translation, bool touching, bool contained)
{
	_touching = touching;
	_translation = translation;
	_contained = contained;
}

bool Collision::IsTouching() const
{
	return _touching;
}

bool Collision::IsContained() const
{
	return _contained;
}


const Vector2& Collision::GetTranslation() const
{
	return _translation;
}
