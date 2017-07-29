#include <Crash2D/collision.hpp>
#include <Crash2D/vector2.hpp>

namespace Crash2D
{
Collision::Collision() :
	_doesOverlap(0), _intersects(std::vector<Vector2>(0)), _aContainsb(0), _bContainsa(0), _displacement(Vector2(0, 0))
{
}

Collision::Collision(bool dI, const std::vector<Vector2> i, bool aCb, bool bCa, const Vector2 t)
	: _doesOverlap(dI), _intersects(i), _aContainsb(aCb), _bContainsa(bCa), _displacement(t)
{
}

const bool Collision::Overlaps() const
{
	return _doesOverlap;
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

const Vector2& Collision::GetDisplacement() const
{
	return _displacement;
}

const Collision Collision::operator - (void) const
{
	return Collision(_doesOverlap, _intersects, _bContainsa, _aContainsb, -_displacement);
}
}
