#include "shape.hpp"

#include <gtest/gtest.h>
#include <cmath>

TEST(Shape, DefaultConstructor)
{
	Shape s;

	EXPECT_EQ(0	, s.GetPos().x);
	EXPECT_EQ(0, s.GetPos().y);
}


TEST(Shape, SetPos)
{
	Shape s;
	s.SetPos(Vector2(2, 17));

	EXPECT_EQ(2, s.GetPos().x);
	EXPECT_EQ(17, s.GetPos().y);
}

TEST(Shape, Move)
{
	Shape s;
	s.SetPos(Vector2(8, -8));
	s.Move(Vector2(8, 8));

	EXPECT_EQ(16, s.GetPos().x);
	EXPECT_EQ(0, s.GetPos().y);
}

TEST(Shape, SetPointCount)
{
	Shape p;
	p.SetPointCount(3);

	EXPECT_EQ(3	, p.GetPointCount());
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


TEST(Shape, Rotate)
{
	Shape s;

	s.Rotate(45);
	EXPECT_EQ(45, s.GetRotation());
}

TEST(Shape, SetRotation)
{
	Shape s;

	s.SetRotation(45);
	EXPECT_EQ(45, s.GetRotation());

	s.SetRotation(-45);
	EXPECT_EQ(315, s.GetRotation());
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
