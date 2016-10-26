#include "shape.hpp"
#include "transform.hpp"

#include <gtest/gtest.h>
#include <cmath>

TEST(Shape, DefaultConstructor)
{
	Shape s;

	EXPECT_EQ(0, s.GetPointCount());
}

TEST(Shape, SetPointCount)
{
	Shape p;
	p.SetPointCount(3);

	EXPECT_EQ(3, p.GetPointCount());
}

TEST(Shape, SetPoint)
{
	Shape p;
	p.SetPointCount(2);
	p.SetPoint(0, Vector2(9, 7));
	p.SetPoint(1, Vector2(8, -4));

	EXPECT_EQ(9	, p.GetPoint(0).x);
	EXPECT_EQ(7	, p.GetPoint(0).y);
	EXPECT_EQ(8	, p.GetPoint(1).x);
	EXPECT_EQ(-4, p.GetPoint(1).y);
}

TEST(Shape, GetTransformedPoint)
{
	Shape s;
	s.SetPointCount(2);
	s.SetPoint(0, Vector2(4, 4));
	s.SetPoint(1, Vector2(-4, -4));

	Transform t;

	EXPECT_EQ(0, s.GetTransformedCenter(t).x);
	EXPECT_EQ(0, s.GetTransformedCenter(t).y);
	EXPECT_EQ(4, s.GetTransformedPoint(0, t).x);
	EXPECT_EQ(4, s.GetTransformedPoint(0, t).y);
	EXPECT_EQ(-4, s.GetTransformedPoint(1, t).x);
	EXPECT_EQ(-4, s.GetTransformedPoint(1, t).y);

	// Rotate
	t.SetRotation(30);

	EXPECT_EQ(0, s.GetTransformedCenter(t).x);
	EXPECT_EQ(0, s.GetTransformedCenter(t).y);
	EXPECT_FLOAT_EQ(2 + 2 * sqrt(3), s.GetTransformedPoint(0, t).x);
	EXPECT_FLOAT_EQ(-2 + 2 * sqrt(3), s.GetTransformedPoint(0, t).y);
	EXPECT_FLOAT_EQ(-2 - 2 * sqrt(3), s.GetTransformedPoint(1, t).x);
	EXPECT_FLOAT_EQ(2 - 2 * sqrt(3), s.GetTransformedPoint(1, t).y);
}

TEST(Shape, GetPoints)
{
	Shape s;
	s.SetPointCount(2);
	s.SetPoint(0, Vector2(3, 4));
	s.SetPoint(1, Vector2(-5, -8));

	std::vector<Vector2> pt = s.GetPoints();
	EXPECT_EQ(2, pt.size());

	EXPECT_EQ(3, pt[0].x);
	EXPECT_EQ(4, pt[0].y);

	EXPECT_EQ(-5, pt[1].x);
	EXPECT_EQ(-8, pt[1].y);
}
