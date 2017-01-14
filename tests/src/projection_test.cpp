#include "helper_func.hpp"

TEST(Projection, DefaultConstructor)
{
	Projection p;
	ARE_EQ(0, p.min);
	ARE_EQ(0, p.max);
}

TEST(Projection, ConstructFromMinMax)
{
	Projection p(9, 87);
	ARE_EQ(9, p.min);
	ARE_EQ(87, p.max);
}

TEST(Projection, IsOverlap)
{
	Projection pA(3, 4);
	Projection pB(-3, 4);

	EXPECT_TRUE(pA.IsOverlap(pB));

	pB = Projection(-3, -4);

	EXPECT_FALSE(pA.IsOverlap(pB));
}

TEST(Projection, GetOverlap)
{
	Projection pA(3, 4);
	Projection pB(-3, 4);

	ARE_EQ(1, pA.GetOverlap(pB));
}
