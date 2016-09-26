#include <gtest/gtest.h>

#include "projection.hpp"

TEST(Projection, DefaultConstructor)
{
	Projection p;
	EXPECT_EQ(0, p.x);
	EXPECT_EQ(0, p.y);
}

TEST(Projection, ConstructFromXY)
{
	Projection p(9, 87);
	EXPECT_EQ(9, p.x);
	EXPECT_EQ(87, p.y);
}

TEST(Projection, ConstructFromVector)
{
	Projection p(Vector2(9, 87));
	EXPECT_EQ(9, p.x);
	EXPECT_EQ(87, p.y);
} 

TEST(Projection, IsOverlap)
{
	Projection pA(3,4);
	Projection pB(-3,4);
	
	EXPECT_TRUE(pA.IsOverlap(pB));
	
	pB = Projection(-3,-4);
	
	EXPECT_FALSE(pA.IsOverlap(pB));
}

TEST(Projection, GetOverlap)
{
	Projection pA(3,4);
	Projection pB(-3,4);
	
	EXPECT_EQ(1, pA.GetOverlap(pB));
}
