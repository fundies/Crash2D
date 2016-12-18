#include "collision.hpp"
#include "vector2.hpp"

Collision::Collision(bool dI, const std::vector<Vector2> i, bool aCb, bool bCa, const Vector2 t)
	: _doesIntersect(dI), _intersects(i), _aContainsb(aCb), _bContainsa(bCa), _translation(t)
{
}

const bool Collision::Intersects() const
{
	return _doesIntersect;
}

const std::vector<Vector2>& Collision::GetIntersects() const
{
	return _intersects;
}

const bool Collision::AcontainsB() const
{
	return _aContainsb;
}

const bool Collision::BcontainsA() const
{
	return _bContainsa;
}

const Vector2& Collision::GetTranslation() const
{
	return _translation;
}
