#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "vector2.hpp"

class Collision
{
private:
	bool _touching;
	Vector2 _translation;

public:

	Collision(Vector2 translation, bool touching);
	bool IsTouching() const;
	const Vector2& GetTranslation() const;
};

#endif
