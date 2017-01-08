#include "circle.hpp"
#include "projection.hpp"
#include "polygon.hpp"
#include "segment.hpp"

#include <gtest/gtest.h>

TEST(Circle, DefaultConstructor)
{
	Circle c;

	EXPECT_EQ(0, c.GetRadius());
	EXPECT_EQ(0, c.GetCenter().x);
	EXPECT_EQ(0, c.GetCenter().y);
}

TEST(Circle, ConstructorRadius)
{
	Circle c(5);

	EXPECT_EQ(5, c.GetRadius());
	EXPECT_EQ(0, c.GetCenter().x);
	EXPECT_EQ(0, c.GetCenter().y);
}

TEST(Circle, SetGetRadius)
{
	Circle c(5);

	EXPECT_EQ(5, c.GetRadius());
	EXPECT_EQ(0, c.GetCenter().x);
	EXPECT_EQ(0, c.GetCenter().y);

	c.SetRadius(8);
	EXPECT_EQ(8, c.GetRadius());
}

TEST(Circle, Project)
{
	Circle c(5);
	Projection p = c.Project(Axis(5, 5));

	EXPECT_FLOAT_EQ(-5, p.x);
	EXPECT_FLOAT_EQ(5, p.y);
}

TEST(Circle, ContainsPoint)
{
	Circle c(5);
	EXPECT_TRUE(c.Contains(Vector2(0, 0)));
	EXPECT_FALSE(c.Contains(Vector2(6, 0)));
}

TEST(Circle, ContainsPolygon)
{
	Circle c(50);

	Polygon a;
	a.SetPointCount(3);
	a.SetPoint(0, Vector2(-10, 0));
	a.SetPoint(1, Vector2(0, 10));
	a.SetPoint(2, Vector2(10, 0));

	EXPECT_TRUE(c.Contains(a));

	Polygon b;
	b.SetPointCount(3);
	b.SetPoint(0, Vector2(-10, 0));
	b.SetPoint(1, Vector2(0, 10));
	b.SetPoint(2, Vector2(51, 0));

	EXPECT_FALSE(c.Contains(b));
}
