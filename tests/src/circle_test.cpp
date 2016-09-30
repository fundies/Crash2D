#include "circle.hpp"

#include <gtest/gtest.h>
#include <cmath>

TEST(Circle, Constructor1Radius)
{
	Circle c(0);

	EXPECT_EQ(0, c.getRadius());
}

TEST(Circle, Project)
{
	Circle c(1);

	Vector2 a;
	Projection pj = c.Project(a);
	Precision_t v = a.Dot(c.GetPos());

	EXPECT_EQ(v - c.GetRadius(), pj.x);
	EXPECT_EQ(v + c.GetRadius(), pj.y);
}