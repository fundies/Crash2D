#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "vector2.hpp"

class Collision
{
public:
	Collision(const Vector2 &t, const bool &v, const bool c);
	bool IsTouching() const;
	bool IsContained() const;
	const Vector2& GetTranslation() const;

private:
	bool _touching;
	bool _contained;
	Vector2 _translation;

};

#endif
