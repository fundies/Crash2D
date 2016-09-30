#include "circle.hpp"

#include <gtest/gtest.h>
#include <cmath>

TEST(Circle, Constructor1Radius)
{
	Circle c(0);

	EXPECT_EQ(0, c.GetRadius());
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

TEST(Circle, CollisionCircle)
{
	Circle cir1(5), cir2(10);

	Collision c = cir1.GetCollision(cir2);
	EXPECT_FALSE(c.IsTouching());
	EXPECT_TRUE(c.IsContained());

	// Move
	cir2.SetPos(Vector2(30, 20));
	c = cir1.GetCollision(cir2);
	EXPECT_TRUE(c.IsTouching());
	EXPECT_FALSE(c.IsContained());
}
