#include "helper.hpp"
#include "vector2.hpp"

TEST(Vector2, DefaultConstructor)
{
	const Vector2 v;
	ARE_EQ(0, v.x);
	ARE_EQ(0, v.y);
}

TEST(Vector2, ConstructFromXY)
{
	const Vector2 v(9, 87);
	ARE_EQ(9, v.x);
	ARE_EQ(87, v.y);
}

TEST(Vector2, CopyConstructor)
{
	Vector2 v1(9, 87);
	Vector2 v2(v1);

	ARE_EQ(9, v2.x);
	ARE_EQ(87, v2.y);
}

TEST(Vector2, DivisionOperator)
{
	/*Vector2 v(40, 60);
	v /= static_cast<Precision_t>(2);

	ARE_EQ(20, v.x);
	ARE_EQ(30, v.y);*/
}

TEST(Vector2, Perpendicular)
{
	Vector2 v(10, 15);
	Vector2 perp(v.Perpendicular());

	ARE_EQ(15, perp.x);
	ARE_EQ(-10, perp.y);
}

TEST(Vector2, DotProduct)
{
	Vector2 a(8, 9);
	Vector2 b(-10, -15);

	ARE_EQ(-215, a.Dot(b));
}

TEST(Vector2, CrossProduct)
{
	/*Vector2 a(15, 3);
	Vector2 b(-8, 2);

	ARE_EQ(54, a.Cross(b));

	a = Vector2(84.87, 58.35);
	b = Vector2(42.435, 29.175);

	ARE_EQ(0, a.Cross(b));*/
}

TEST(Vector2, Magnitude)
{
	Vector2 v(-6, -8);

	ARE_EQ(10, v.Length());
}

TEST(Vector2, Normalize)
{
	Vector2 v(10, -5);
	v = v.Normalize();

	ARE_EQ(2 / std::sqrt(5), v.x);
	ARE_EQ(-1 / std::sqrt(5), v.y);
}

TEST(Vector2, AsFloat)
{
	Vector2 v((double)1.5, (double)2.3);

	ARE_EQ(1.5f, v.x);
	ARE_EQ(2.3f, v.y);
}

TEST(Vector2, GetDistance)
{
	Vector2 a(0, 0);
	Vector2 b(10, 10);
	ARE_EQ(10 * std::sqrt(2), a.GetDistance(b));
	ARE_EQ(10 * std::sqrt(2), b.GetDistance(a));

	Vector2 c(0, 0);
	Vector2 d(-10, -10);
	ARE_EQ(10 * std::sqrt(2), c.GetDistance(d));
	ARE_EQ(10 * std::sqrt(2), d.GetDistance(c));
}
