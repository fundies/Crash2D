#include "segment.hpp"
#include "transform.hpp"

#include <gtest/gtest.h>
#include <cmath>

TEST(Segment, DefaultConstructor)
{
	Segment l;

	EXPECT_EQ(0, l.GetPoint(0).x);
	EXPECT_EQ(0, l.GetPoint(0).y);

	EXPECT_EQ(0, l.GetPoint(1).x);
	EXPECT_EQ(0, l.GetPoint(1).y);

	EXPECT_FLOAT_EQ(std::numeric_limits<Precision_t>::infinity(), l.GetSlope());

	EXPECT_FLOAT_EQ(0, l.GetCenter().x);
	EXPECT_FLOAT_EQ(0, l.GetCenter().y);
}

TEST(Segment, Constructor2Points)
{
	Segment l(Vector2(0, 0), Vector2(10, 10));

	EXPECT_EQ(0	, l.GetPoint(0).x);
	EXPECT_EQ(0, l.GetPoint(0).y);

	EXPECT_EQ(10, l.GetPoint(1).x);
	EXPECT_EQ(10, l.GetPoint(1).y);

	EXPECT_FLOAT_EQ(1, l.GetSlope());

	EXPECT_EQ(5, l.GetCenter().x);
	EXPECT_EQ(5, l.GetCenter().y);
}

TEST(Segment, SetPoint)
{
	Segment l;

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

TEST(Segment, DistancePoint)
{
	Segment l(Vector2(2, 2), Vector2(10, 5));
	Vector2 v(0, 0);;

	Transform t;

	// Outside
	//EXPECT_FLOAT_EQ(2 * std::sqrt(2), l.DistancePoint(v));

	// Below
	v = Vector2(4, 3);
	EXPECT_FLOAT_EQ(2 / std::sqrt(73), l.DistancePoint(v, t));

	//Above
	v = Vector2(3, 4);
	EXPECT_FLOAT_EQ(13 / std::sqrt(73), l.DistancePoint(v, t));

}

TEST(Segment, SignedDistancePoint)
{
	Segment l(Vector2(2, 2), Vector2(10, 5));
	Vector2 v(0, 0);

	Transform t;

	// Outside
	//EXPECT_FLOAT_EQ(2 * std::sqrt(2), l.SignedDistancePoint(v));

	// On
	v = Vector2(10, 5);
	EXPECT_FLOAT_EQ(0, l.SignedDistancePoint(v, t));

	v = Vector2(2, 2);
	EXPECT_FLOAT_EQ(0, l.SignedDistancePoint(v, t));

	// Below
	v = Vector2(4, 3);
	EXPECT_FLOAT_EQ(-2 / std::sqrt(73), l.SignedDistancePoint(v, t));

	//Above
	v = Vector2(3, 4);
	EXPECT_FLOAT_EQ(-13 / std::sqrt(73), l.SignedDistancePoint(v, t));

}

TEST(Segment, GetLength)
{
	Vector2 a(0, 0);
	Vector2 b(10, 10);

	Segment l(a, b);

	Transform t;

	EXPECT_FLOAT_EQ(10 * std::sqrt(2), l.GetLength(t));
}

TEST(Segment, IsPerpendicular)
{
	Segment l1(Vector2(0, 0), Vector2(10, 0));
	Segment l2(Vector2(4, 4), Vector2(4, -4));

	Transform t;

	EXPECT_TRUE(l1.IsPerpendicular(l2, t, t));

	l1 = Segment(Vector2(0, 0), Vector2(4, 4));
	l2 = Segment(Vector2(0, 0), Vector2(4, -4));

	EXPECT_TRUE(l1.IsPerpendicular(l2, t, t));

	l2 = Segment(Vector2(0, 0), Vector2(-4, -4));

	EXPECT_FALSE(l1.IsPerpendicular(l2, t, t));
}

TEST(Segment, IsParallel)
{
	Segment l1(Vector2(5, 5), Vector2(5, -5));
	Segment l2(Vector2(4, 4), Vector2(4, -4));

	Transform t;

	EXPECT_TRUE(l1.IsParallel(l2, t, t));

	l1 = Segment(Vector2(0, 0), Vector2(4, 4));
	l2 = Segment(Vector2(0, 0), Vector2(-4, -4));

	EXPECT_TRUE(l1.IsParallel(l2, t, t));

	l2 = Segment(Vector2(0, 0), Vector2(-4, 4));

	EXPECT_FALSE(l1.IsParallel(l2, t, t));
}

TEST(Segment, ContainsPoint)
{
	Segment l(Vector2(0, 0), Vector2(10, 10));

	Transform t;

	Segment l2(Vector2(3.43, 7.87), Vector2(88.3, 66.22));
	EXPECT_TRUE(l2.ContainsPoint(Vector2(45.865, 37.045), t));

	EXPECT_TRUE(l.ContainsPoint(Vector2(5, 5), t));
	EXPECT_FALSE(l.ContainsPoint(Vector2(-1, -1), t));
	EXPECT_FALSE(l.ContainsPoint(Vector2(0, 2), t));

	t.SetTranslation(Vector2(300, 400));

	EXPECT_TRUE(l.ContainsPoint(Vector2(300, 400), t));

	t.Rotate(30);

	EXPECT_FALSE(l.ContainsPoint(Vector2(300, 400), t));;
}

TEST(Segment, GetIntersect)
{
	Segment l1(Vector2(5, 5), Vector2(5, -5));
	Segment l2(Vector2(4, 4), Vector2(-4, -4));

	Transform t1;
	Transform t2;

	Vector2 i = l1.GetIntersect(l2, t1, t2);
	EXPECT_EQ(5, i.x);
	EXPECT_EQ(5, i.y);

	t2.Rotate(30);
	i = l1.GetIntersect(l2, t1, t2);

	EXPECT_EQ(5, i.x);
	EXPECT_FLOAT_EQ(-5 * (sqrt(3) - 2), i.y);
}

TEST(Segment, Intersects)
{
	Transform t;

	Segment l1(Vector2(0, 0), Vector2(5, 5));
	Segment l2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(l1.Intersects(l2, t, t));
	EXPECT_TRUE(l2.Intersects(l1, t, t));

	Segment l3(Vector2(0, 0), Vector2(5, 5));
	Segment l4(Vector2(5, 5), Vector2(10, 10));

	EXPECT_TRUE(l3.Intersects(l4, t, t));
	EXPECT_TRUE(l4.Intersects(l3, t, t));
}

TEST(Segment, GetAxis)
{
	Segment l1(Vector2(0, 0), Vector2(5, 5));

	Vector2 a = l1.GetAxis();

	EXPECT_EQ(-1 / std::sqrt(2), a.x);
	EXPECT_EQ(1 / std::sqrt(2), a.y);
}
