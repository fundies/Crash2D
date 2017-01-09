#include "polygon.hpp"
#include "circle.hpp"
#include "segment.hpp"
#include "projection.hpp"
#include "collision.hpp"

#include <gtest/gtest.h>
#include <cmath>

TEST(Polygon, DefaultConstructor)
{
	Polygon p;

	EXPECT_EQ(0	, p.GetPos().x);
	EXPECT_EQ(0, p.GetPos().y);
	EXPECT_EQ(0	, p.GetPointCount());
	EXPECT_EQ(0, p.GetRotation());
}

TEST(Polygon, GenerateAxis)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(3, 0));
	p.SetPoint(1, Vector2(6, 3));
	p.SetPoint(2, Vector2(-3, 3));
	p.ReCalc();

	AxesVec axes = p.GetAxes();
	EXPECT_EQ(3, axes.size());

	EXPECT_FLOAT_EQ(-1 / std::sqrt(2), axes[0].x);
	EXPECT_FLOAT_EQ(1 / std::sqrt(2), axes[0].y);

	EXPECT_EQ(0, axes[1].x);
	EXPECT_EQ(-1, axes[1].y);

	EXPECT_FLOAT_EQ(1 / std::sqrt(5), axes[2].x);
	EXPECT_FLOAT_EQ(2 / std::sqrt(5), axes[2].y);
}

TEST(Polygon, GetCenter)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(3, 0));
	p.SetPoint(1, Vector2(6, 3));
	p.SetPoint(2, Vector2(-3, 3));
	p.ReCalc();

	EXPECT_EQ(2, p.GetCenter().x);
	EXPECT_EQ(2, p.GetCenter().y);
}


TEST(Polygon, Project)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(3, 0));
	p.SetPoint(1, Vector2(6, 3));
	p.SetPoint(2, Vector2(-3, 3));
	p.ReCalc();

	AxesVec axes = p.GetAxes();

	Projection pj = p.Project(axes[0]);
	EXPECT_FLOAT_EQ(-1 / std::sqrt(2) * 3, pj.x);
	EXPECT_FLOAT_EQ(1 / std::sqrt(2) * 6, pj.y);

	pj = p.Project(axes[1]);
	EXPECT_FLOAT_EQ(-3, pj.x);
	EXPECT_FLOAT_EQ(0, pj.y);

	pj = p.Project(axes[2]);
	EXPECT_FLOAT_EQ(1 / std::sqrt(5) * 3, pj.x);
	EXPECT_FLOAT_EQ(2 / std::sqrt(5) * 6, pj.y);
}

TEST(Polygon, CollisionPolygon)
{
	Polygon pA;
	pA.SetPointCount(3);
	pA.SetPoint(0, Vector2(60, 0));
	pA.SetPoint(1, Vector2(90, 30));
	pA.SetPoint(2, Vector2(0, 30));
	pA.ReCalc();

	Polygon pB;
	pB.SetPointCount(3);
	pB.SetPoint(0, Vector2(120, 0));
	pB.SetPoint(1, Vector2(180, 30));
	pB.SetPoint(2, Vector2(90, 30));
	pB.ReCalc();

	Collision c = pA.GetCollision(pB);
	EXPECT_TRUE(c.Overlaps());
	EXPECT_FLOAT_EQ(0.707107, c.GetDisplacement().x);
	EXPECT_FLOAT_EQ(-0.707107, c.GetDisplacement().y);

	// MOVE
	pB.Move(Vector2(1, 0));
	c = pA.GetCollision(pB);
	EXPECT_FALSE(c.Overlaps());

	// ROTATE
	pB.Move(Vector2(-1, 0));
	pB.Rotate(180);
	c = pA.GetCollision(pB);
	EXPECT_FALSE(c.Overlaps());

	pB.Move(Vector2(-10, 0));
	c = pA.GetCollision(pB);
	EXPECT_TRUE(c.Overlaps());
	EXPECT_FLOAT_EQ(0.707107, c.GetDisplacement().x);
	EXPECT_FLOAT_EQ(-0.707107, c.GetDisplacement().y);

	// Move Displacement
	pB.Move(c.GetDisplacement());
	c = pA.GetCollision(pB);
	EXPECT_FALSE(c.Overlaps());

	//Contains
	Polygon pC;
	pC.SetPointCount(4);
	pC.SetPoint(0, Vector2(0, 0));
	pC.SetPoint(1, Vector2(50, 0));
	pC.SetPoint(2, Vector2(50, 50));
	pC.SetPoint(3, Vector2(0, 50));
	pC.ReCalc();

	Polygon pD;
	pD.SetPointCount(4);
	pD.SetPoint(0, Vector2(1, 1));
	pD.SetPoint(1, Vector2(25, 1));
	pD.SetPoint(2, Vector2(25, 25));
	pD.SetPoint(3, Vector2(1, 25));
	pD.ReCalc();

	c = pD.GetCollision(pC);
	EXPECT_FALSE(c.AcontainsB());

	c = pC.GetCollision(pD);
	EXPECT_TRUE(c.AcontainsB());

	pD.Move(c.GetDisplacement());
	c = pD.GetCollision(pC);
	EXPECT_FALSE(c.Overlaps());
}

TEST(Polygon, CollisionCircle)
{
	Polygon pA;
	pA.SetPointCount(3);
	pA.SetPoint(0, Vector2(60, 0));
	pA.SetPoint(1, Vector2(90, 30));
	pA.SetPoint(2, Vector2(0, 30));
	pA.ReCalc();

	Circle cir(5);

	Collision c = pA.GetCollision(cir);
	EXPECT_FALSE(c.Overlaps());

	// Move
	cir.SetPos(Vector2(30, 20));
	c = pA.GetCollision(cir);
	EXPECT_TRUE(c.Overlaps());

	// Move Displacement
	cir.Move(-c.GetDisplacement());
	c = pA.GetCollision(cir);

	EXPECT_FALSE(c.Overlaps());
	EXPECT_FALSE(c.AcontainsB());

	// Contains
	cir.SetPos(Vector2(60, 24));
	c = pA.GetCollision(cir);

	EXPECT_TRUE(c.AcontainsB());

	cir.Move(-c.GetDisplacement());
	c = pA.GetCollision(cir);

	EXPECT_FALSE(c.Overlaps());

	// Need further testing here. Seems to take two displacements sometimes?
}

TEST(Polygon, ContainsPoint)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(3, 0));
	p.SetPoint(1, Vector2(6, 3));
	p.SetPoint(2, Vector2(-3, 3));
	p.ReCalc();

	// Edge
	EXPECT_TRUE(p.Contains(Vector2(3, 0)));
	EXPECT_TRUE(p.Contains(Vector2(6, 3)));
	EXPECT_TRUE(p.Contains(Vector2(-3, 3)));

	// Inside
	EXPECT_TRUE(p.Contains(Vector2(3, 2)));

	// Outside
	EXPECT_FALSE(p.Contains(Vector2(7, 3)));

	// Square
	Polygon s;
	s.SetPointCount(4);
	s.SetPoint(0, Vector2(0, 0));
	s.SetPoint(1, Vector2(3, 0));
	s.SetPoint(2, Vector2(3, 3));
	s.SetPoint(3, Vector2(0, 3));
	s.ReCalc();

	// Edge
	EXPECT_TRUE(s.Contains(Vector2(0, 0)));

	// Inside
	EXPECT_TRUE(s.Contains(Vector2(.5, .5)));
	EXPECT_TRUE(s.Contains(Vector2(2.5, 2.5)));

	// Outside
	EXPECT_FALSE(s.Contains(Vector2(3, 4)));

	// Move
	s.Move(Vector2(30, 30));

	// Edge
	EXPECT_TRUE(s.Contains(Vector2(30, 30)));

	// Inside
	EXPECT_TRUE(s.Contains(Vector2(30.5, 30.5)));
	EXPECT_TRUE(s.Contains(Vector2(32.5, 32.5)));

	// Outside
	EXPECT_FALSE(s.Contains(Vector2(33, 34)));

	// Rotate
	s.Rotate(45);

	// Edge
	EXPECT_TRUE(s.Contains(Vector2(29.3787, 31.5)));
	EXPECT_FALSE(s.Contains(Vector2(30, 30)));

	// Inside
	EXPECT_TRUE(s.Contains(Vector2(30.5, 30.5)));
	EXPECT_TRUE(s.Contains(Vector2(32.5, 32.5)));

	// Outside
	EXPECT_FALSE(s.Contains(Vector2(33, 34)));

}

TEST(Polygon, ContainsPolygon)
{
	Polygon pA;
	pA.SetPointCount(3);
	pA.SetPoint(0, Vector2(0, 0));
	pA.SetPoint(1, Vector2(300, 300));
	pA.SetPoint(2, Vector2(600, 300));
	pA.ReCalc();

	Polygon pB;
	pB.SetPointCount(3);
	pB.SetPoint(0, Vector2(28, 20));
	pB.SetPoint(1, Vector2(320, 260));
	pB.SetPoint(2, Vector2(500, 260));
	pB.ReCalc();

	EXPECT_TRUE(pA.Contains(pB));
	EXPECT_FALSE(pB.Contains(pA));

	// Move Overlap
	pB.Move(Vector2(40, 0));
	EXPECT_FALSE(pA.Contains(pB));
	EXPECT_FALSE(pB.Contains(pA));
}

TEST(Polygon, Rotate)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(3, 0));
	p.SetPoint(1, Vector2(6, 3));
	p.SetPoint(2, Vector2(-3, 3));
	p.ReCalc();

	p.Rotate(45);
	EXPECT_EQ(45, p.GetRotation());

	EXPECT_FLOAT_EQ(3 / std::sqrt(2) - 2 * (-1 + std::sqrt(2)), p.GetPoint(0).x);
	EXPECT_FLOAT_EQ(2 - 3 / std::sqrt(2), p.GetPoint(0).y);

	EXPECT_FLOAT_EQ(3 / std::sqrt(2) + 3 * std::sqrt(2) - 2 * (-1 + std::sqrt(2)), p.GetPoint(1).x);
	EXPECT_FLOAT_EQ(2 + 3 / std::sqrt(2) - 3 * std::sqrt(2), p.GetPoint(1).y);

	EXPECT_FLOAT_EQ(-2 * (-1 + std::sqrt(2)), p.GetPoint(2).x);
	EXPECT_FLOAT_EQ(2 + 3 * std::sqrt(2), p.GetPoint(2).y);
}

TEST(Polygon, ContainsCircle)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(30, 0));
	p.SetPoint(1, Vector2(60, 30));
	p.SetPoint(2, Vector2(-30, 30));
	p.ReCalc();

	Circle c(5);

	EXPECT_FALSE(p.Contains(c));

	c.Move(Vector2(30, 20));
	EXPECT_TRUE(p.Contains(c));

	p.Move(Vector2(-5, -5));
	EXPECT_FALSE(p.Contains(c));
}

TEST(Polygon, SetRotation)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(3, 0));
	p.SetPoint(1, Vector2(6, 3));
	p.SetPoint(2, Vector2(-3, 3));
	p.ReCalc();

	p.SetRotation(45);
	EXPECT_EQ(45, p.GetRotation());

	EXPECT_FLOAT_EQ(3 / std::sqrt(2) - 2 * (-1 + std::sqrt(2)), p.GetPoint(0).x);
	EXPECT_FLOAT_EQ(2 - 3 / std::sqrt(2), p.GetPoint(0).y);

	EXPECT_FLOAT_EQ(3 / std::sqrt(2) + 3 * std::sqrt(2) - 2 * (-1 + std::sqrt(2)), p.GetPoint(1).x);
	EXPECT_FLOAT_EQ(2 + 3 / std::sqrt(2) - 3 * std::sqrt(2), p.GetPoint(1).y);

	EXPECT_FLOAT_EQ(-2 * (-1 + std::sqrt(2)), p.GetPoint(2).x);
	EXPECT_FLOAT_EQ(2 + 3 * std::sqrt(2), p.GetPoint(2).y);

	p.SetRotation(-45);
	EXPECT_EQ(315, p.GetRotation());

	EXPECT_FLOAT_EQ(2 + 3 / std::sqrt(2), p.GetPoint(0).x);
	EXPECT_FLOAT_EQ(3 / std::sqrt(2) - 2 * (-1 + std::sqrt(2)), p.GetPoint(0).y);

	EXPECT_FLOAT_EQ(2 - 3 / std::sqrt(2) + 3 * std::sqrt(2), p.GetPoint(1).x);
	EXPECT_FLOAT_EQ(3 / std::sqrt(2) + 3 * std::sqrt(2) - 2 * (-1 + std::sqrt(2)), p.GetPoint(1).y);

	EXPECT_FLOAT_EQ(2 - 3 * std::sqrt(2), p.GetPoint(2).x);
	EXPECT_FLOAT_EQ(-2 * (-1 + std::sqrt(2)), p.GetPoint(2).y);
}
