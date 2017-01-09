#include "segment.hpp"

#include <gtest/gtest.h>
#include <cmath>

TEST(Segment, DefaultConstructor)
{
	Segment l;

	EXPECT_EQ(0	, l.GetPoint(0).x);
	EXPECT_EQ(0, l.GetPoint(0).y);

	EXPECT_EQ(0, l.GetPoint(1).x);
	EXPECT_EQ(0, l.GetPoint(1).y);

	EXPECT_FLOAT_EQ(0, l.GetSlope());

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
	l.Recalc();

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

TEST(Segment, SignedDistancePoint)
{
	Segment l(Vector2(2, 2), Vector2(10, 5));
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

TEST(Segment, GetLength)
{
	Vector2 a(0, 0);
	Vector2 b(10, 10);

	Segment l(a, b);

	EXPECT_FLOAT_EQ(10 * std::sqrt(2), l.GetLength());
}

TEST(Segment, IsPerpendicular)
{
	Segment l1(Vector2(0, 0), Vector2(10, 0));
	Segment l2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(l1.IsPerpendicular(l2));

	l1 = Segment(Vector2(0, 0), Vector2(4, 4));
	l2 = Segment(Vector2(0, 0), Vector2(4, -4));

	EXPECT_TRUE(l1.IsPerpendicular(l2));

	l2 = Segment(Vector2(0, 0), Vector2(-4, -4));

	EXPECT_FALSE(l1.IsPerpendicular(l2));
}

TEST(Segment, IsParallel)
{
	Segment l1(Vector2(5, 5), Vector2(5, -5));
	Segment l2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(l1.IsParallel(l2));

	l1 = Segment(Vector2(0, 0), Vector2(4, 4));
	l2 = Segment(Vector2(0, 0), Vector2(-4, -4));

	EXPECT_TRUE(l1.IsParallel(l2));

	l2 = Segment(Vector2(0, 0), Vector2(-4, 4));

	EXPECT_FALSE(l1.IsParallel(l2));
}

TEST(Segment, ContainsPoint)
{
	Segment l(Vector2(0, 0), Vector2(10, 10));

	EXPECT_TRUE(l.Contains(Vector2(5, 5)));
	EXPECT_FALSE(l.Contains(Vector2(-1, -1)));
	EXPECT_FALSE(l.Contains(Vector2(0, 2)));

	l.Move(Vector2(300, 400));
	EXPECT_TRUE(l.Contains(Vector2(300, 400)));

	l.Rotate(30);
	EXPECT_FALSE(l.Contains(Vector2(300, 400)));

	Segment l2(Vector2(3.43, 7.87), Vector2(88.3, 66.22));
	EXPECT_TRUE(l2.Contains(Vector2(45.865, 37.045)));
}

TEST(Segment, GetIntersects)
{
	Segment l1(Vector2(5, 5), Vector2(5, -5));
	Segment l2(Vector2(4, 4), Vector2(-4, -4));

	std::vector<Vector2> i = l1.GetIntersects(l2);
	EXPECT_EQ(0, i.size());

	l2.SetPoint(0, Vector2(5, 4));

	i = l1.GetIntersects(l2);
	EXPECT_EQ(1, i.size());

	if (i.size() > 0)
	{
		EXPECT_EQ(5, i[0].x);
		EXPECT_EQ(4, i[0].y);
	}

	//l2.Rotate(30);
	//i = l1.GetIntersects(l2);
}

TEST(Segment, Overlaps)
{
	Segment l1(Vector2(0, 0), Vector2(5, 5));
	Segment l2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(l1.Overlaps(l2));
	EXPECT_TRUE(l2.Overlaps(l1));

	Segment l3(Vector2(0, 0), Vector2(5, 5));
	Segment l4(Vector2(5, 5), Vector2(10, 10));

	EXPECT_TRUE(l3.Overlaps(l4));
	EXPECT_TRUE(l4.Overlaps(l3));
}

TEST(Segment, GetAxis)
{
	Segment l1(Vector2(0, 0), Vector2(5, 5));

	Vector2 a = l1.GetAxis();

	EXPECT_EQ(-1 / std::sqrt(2), a.x);
	EXPECT_EQ(1 / std::sqrt(2), a.y);
}

TEST(Segment, GetDisplacement)
{
	Segment l1(Vector2(0, 0), Vector2(5, 5));
	Segment l2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(l1.Overlaps(l2));

	Vector2 v = l1.GetDisplacement(l2);
	l2.Move(v);

	EXPECT_FALSE(l1.Overlaps(l2));

	l2.Move(-v);

	v = l2.GetDisplacement(l1);
	l1.Move(v);

	EXPECT_FALSE(l1.Overlaps(l2));
}
