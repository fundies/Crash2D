#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <SFML/Graphics.hpp>

using Precision_t = float;

class Vector2 : public sf::Vector2<Precision_t>
{
public:
	Vector2() : sf::Vector2<Precision_t>(0 ,0) {}
	Vector2(Precision_t x, Precision_t y) : sf::Vector2<Precision_t>(x,y) {}
	Vector2(const sf::Vector2<Precision_t> &v);
	Vector2 perpendicular();
	Precision_t dot(Vector2 v);
	Precision_t cross(Vector2 v);
	Precision_t magnitude();
	Vector2 normalize();

};

using Axis = Vector2;
using AxesVec = std::vector<Axis>;

#endif
