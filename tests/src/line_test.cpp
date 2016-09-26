#include "line.hpp"

#include <gtest/gtest.h>
#include <cmath>

TEST(Line, DefaultConstructor)
{
	Line l;

	EXPECT_EQ(0	, l.GetPoint(0).x);
	EXPECT_EQ(0, l.GetPoint(0).y);

	EXPECT_EQ(0, l.GetPoint(1).x);
	EXPECT_EQ(0, l.GetPoint(1).y);

	EXPECT_FLOAT_EQ(0, l.GetSlope());

	EXPECT_FLOAT_EQ(0, l.GetCenter().x);
	EXPECT_FLOAT_EQ(0, l.GetCenter().y);
}

TEST(Line, Constructor2Points)
{
	Line l(Vector2(0, 0), Vector2(10, 10));

	EXPECT_EQ(0	, l.GetPoint(0).x);
	EXPECT_EQ(0, l.GetPoint(0).y);

	EXPECT_EQ(10, l.GetPoint(1).x);
	EXPECT_EQ(10, l.GetPoint(1).y);

	EXPECT_FLOAT_EQ(1, l.GetSlope());

	EXPECT_EQ(5, l.GetCenter().x);
	EXPECT_EQ(5, l.GetCenter().y);
}

TEST(Line, SetPoint)
{
	Line l;

	l.SetPoint(0, Vector2(9, 6));
	l.SetPoint(1, Vector2(-3, 4));

	EXPECT_EQ(9	, l.GetPoint(0).x);
	EXPECT_EQ(6, l.GetPoint(0).y);

	EXPECT_EQ(-3, l.GetPoint(1).x);
	EXPECT_EQ(4, l.GetPoint(1).y);

	EXPECT_FLOAT_EQ(1.f / 6.f, l.GetSlope());

	EXPECT_EQ(3, l.GetCenter().x);
	EXPECT_EQ(5, l.GetCenter().y);
}

TEST(Line, DistancePoint)
{
	Line l(Vector2(2, 2), Vector2(10, 5));
	Vector2 v(0, 0);

	// Outside
	//EXPECT_FLOAT_EQ(2 * std::sqrt(2), l.DistancePoint(v));

	// Below
	v = Vector2(4, 3);
	EXPECT_FLOAT_EQ(2 / std::sqrt(73), l.DistancePoint(v));

	//Above
	v = Vector2(3, 4);
	EXPECT_FLOAT_EQ(13 / std::sqrt(73), l.DistancePoint(v));

}

TEST(Line, SignedDistancePoint)
{
	Line l(Vector2(2, 2), Vector2(10, 5));
	Vector2 v(0, 0);

	// Outside
	//EXPECT_FLOAT_EQ(2 * std::sqrt(2), l.SignedDistancePoint(v));

	// On
	v = Vector2(10, 5);
	EXPECT_FLOAT_EQ(0, l.SignedDistancePoint(v));

	v = Vector2(2, 2);
	EXPECT_FLOAT_EQ(0, l.SignedDistancePoint(v));

	// Below
	v = Vector2(4, 3);
	EXPECT_FLOAT_EQ(-2 / std::sqrt(73), l.SignedDistancePoint(v));

	//Above
	v = Vector2(3, 4);
	EXPECT_FLOAT_EQ(-13 / std::sqrt(73), l.SignedDistancePoint(v));

}

TEST(Line, GetLength)
{
	Vector2 a(0, 0);
	Vector2 b(10, 10);

	Line l(a, b);

	EXPECT_FLOAT_EQ(10 * std::sqrt(2), l.GetLength());
}

TEST(Line, IsPerpendicular)
{
	Line l1(Vector2(0, 0), Vector2(10, 0));
	Line l2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(l1.IsPerpendicular(l2));

	l1 = Line(Vector2(0, 0), Vector2(4, 4));
	l2 = Line(Vector2(0, 0), Vector2(4, -4));

	EXPECT_TRUE(l1.IsPerpendicular(l2));

	l2 = Line(Vector2(0, 0), Vector2(-4, -4));

	EXPECT_FALSE(l1.IsPerpendicular(l2));
}

TEST(Line, IsParallel)
{
	Line l1(Vector2(5, 5), Vector2(5, -5));
	Line l2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(l1.IsParallel(l2));

	l1 = Line(Vector2(0, 0), Vector2(4, 4));
	l2 = Line(Vector2(0, 0), Vector2(-4, -4));

	EXPECT_TRUE(l1.IsParallel(l2));

	l2 = Line(Vector2(0, 0), Vector2(-4, 4));

	EXPECT_FALSE(l1.IsParallel(l2));
}

TEST(Line, ContainsPoint)
{
	Line l(Vector2(0, 0), Vector2(10, 10));

	EXPECT_TRUE(l.ContainsPoint(Vector2(5, 5)));
	EXPECT_FALSE(l.ContainsPoint(Vector2(-1, -1)));
	EXPECT_FALSE(l.ContainsPoint(Vector2(0, 2)));

	l.Move(Vector2(300, 400));
	EXPECT_TRUE(l.ContainsPoint(Vector2(300, 400)));

	l.Rotate(30);
	EXPECT_FALSE(l.ContainsPoint(Vector2(300, 400)));

	Line l2(Vector2(3.43, 7.87), Vector2(88.3, 66.22));
	EXPECT_TRUE(l2.ContainsPoint(Vector2(45.865, 37.045)));
}

TEST(Line, GetIntersect)
{
	Line l1(Vector2(5, 5), Vector2(5, -5));
	Line l2(Vector2(4, 4), Vector2(-4, -4));

	Vector2 i = l1.GetIntersect(l2);
	EXPECT_EQ(5, i.x);
	EXPECT_EQ(5, i.y);

	l2.Rotate(30);
	i = l1.GetIntersect(l2);
}

TEST(Line, Intersects)
{
	Line l1(Vector2(0, 0), Vector2(5, 5));
	Line l2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(l1.Intersects(l2));
	EXPECT_TRUE(l2.Intersects(l1));

	Line l3(Vector2(0, 0), Vector2(5, 5));
	Line l4(Vector2(5, 5), Vector2(10, 10));

	EXPECT_TRUE(l3.Intersects(l4));
	EXPECT_TRUE(l4.Intersects(l3));
}

TEST(Line, GetAxis)
{
	Line l1(Vector2(0, 0), Vector2(5, 5));

	Vector2 a = l1.GetAxis();

	EXPECT_EQ(-1 / std::sqrt(2), a.x);
	EXPECT_EQ(1 / std::sqrt(2), a.y);
}

TEST(Line, GetTranslation)
{
	Line l1(Vector2(0, 0), Vector2(5, 5));
	Line l2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(l1.Intersects(l2));

	Vector2 v = l1.GetTranslation(l2);
	l2.Move(v);

	EXPECT_FALSE(l1.Intersects(l2));

	l2.Move(-v);

	v = l2.GetTranslation(l1);
	l1.Move(v);

	EXPECT_FALSE(l1.Intersects(l2));
}
