#include "helper_func.hpp"

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
	Circle c(Vector2(0, 0), 5);

	EXPECT_EQ(5, c.GetRadius());
	EXPECT_EQ(0, c.GetCenter().x);
	EXPECT_EQ(0, c.GetCenter().y);
}

// This does nothing
TEST(Circle, ReCalc)
{
	Circle c;
	c.ReCalc();

	EXPECT_EQ(0, c.GetRadius());
}


TEST(Circle, SetGetRadius)
{
	Circle c(Vector2(0, 0), 5);

	EXPECT_EQ(5, c.GetRadius());
	EXPECT_EQ(0, c.GetCenter().x);
	EXPECT_EQ(0, c.GetCenter().y);

	c.SetRadius(8);
	EXPECT_EQ(8, c.GetRadius());
}

TEST(Circle, Project)
{
	Circle c(Vector2(0, 0), 5);
	Projection p = c.Project(Axis(5, 5));

	EXPECT_FLOAT_EQ(-5, p.min);
	EXPECT_FLOAT_EQ(5, p.max);
}

TEST(Circle, ProjectShapeAxis)
{
	Circle c(Vector2(0, 0), 5);
	Projection p = c.Project(c, Axis(5, 5));

	EXPECT_FLOAT_EQ(-5, p.min);
	EXPECT_FLOAT_EQ(5, p.max);
}

TEST(Circle, ContainsPoint)
{
	Circle c(Vector2(0, 0), 5);
	EXPECT_TRUE(c.Contains(Vector2(0, 0)));
	EXPECT_FALSE(c.Contains(Vector2(6, 0)));
}

TEST(Circle, ContainsSegment)
{
	Circle c(Vector2(0, 0), 50);
	Segment s(Vector2(0, 0), Vector2(50, 0));

	EXPECT_TRUE(c.Contains(s));

	s.SetPoint(1, Vector2(51, 0));

	EXPECT_FALSE(c.Contains(s));
}

TEST(Circle, ContainsCircle)
{
	Circle c1(Vector2(0, 0), 50);
	Circle c2(Vector2(10, 10), 25);

	EXPECT_TRUE(c1.Contains(c2));
	EXPECT_FALSE(c2.Contains(c1));
}

TEST(Circle, ContainsPolygon)
{
	Circle c(Vector2(0, 0), 50);

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

TEST(Circle, OverlapsSegment)
{
	Circle c(Vector2(0, 0), 50);
	Segment s(Vector2(50, 0), Vector2(100, 0));

	EXPECT_TRUE(c.Overlaps(s));

	s.SetPoint(0, Vector2(51, 0));

	EXPECT_FALSE(c.Overlaps(s));
}


TEST(Circle, OverlapsCircle)
{
	Circle c1(Vector2(0, 0), 50);
	Circle c2(Vector2(100, 0), 50);
	Circle c3(Vector2(101, 0), 50);

	EXPECT_TRUE(c1.Overlaps(c2));
	EXPECT_FALSE(c1.Overlaps(c3));
}

TEST(Circle, OverlapsPolygon)
{
	Circle c(Vector2(0, 0), 50);

	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(50, 0));
	p.SetPoint(1, Vector2(100, -50));
	p.SetPoint(2, Vector2(100, 50));
	p.ReCalc();

	EXPECT_TRUE(c.Overlaps(p));

	p.SetPoint(0, Vector2(51, 0));
	p.ReCalc();

	EXPECT_FALSE(c.Overlaps(p));
}

TEST(Circle, GetIntersectsSegment)
{
	Circle c(Vector2(0, 0), 50);
	Segment s(Vector2(-50, 0), Vector2(50, 0));

	auto i = c.GetIntersects(s);

	EXPECT_EQ(i.size(), 2);

	EXPECT_EQ(50, i[0].x);
	EXPECT_EQ(0, i[0].y);

	EXPECT_EQ(-50, i[1].x);
	EXPECT_EQ(0, i[1].y);

	s = Segment(Vector2(-50, 50), Vector2(50, 50));
	i = c.GetIntersects(s);

	EXPECT_EQ(i.size(), 1);
	EXPECT_EQ(0, i[0].x);
	EXPECT_EQ(50, i[0].y);

	s = Segment(Vector2(-50, 51), Vector2(50, 51));
	i = c.GetIntersects(s);
	EXPECT_EQ(i.size(), 0);
}

TEST(Circle, GetIntersectsCircle)
{
	Circle c1(Vector2(0, 0), 50);
	Circle c2(Vector2(50, 0), 50);

	auto i = c1.GetIntersects(c2);

	EXPECT_EQ(i.size(), 2);

	EXPECT_EQ(25, i[0].x);
	EXPECT_EQ(-25 * std::sqrt(3), i[0].y);

	EXPECT_EQ(25, i[1].x);
	EXPECT_EQ(25 * std::sqrt(3), i[1].y);

	Circle c3(Vector2(100, 0), 50);

	i = c1.GetIntersects(c3);
	EXPECT_EQ(i.size(), 1);
	EXPECT_EQ(50, i[0].x);
	EXPECT_EQ(0, i[0].y);

	Circle c4(Vector2(101, 0), 50);

	i = c1.GetIntersects(c4);
	EXPECT_EQ(i.size(), 0);
}

TEST(Circle, GetIntersectsPolygon)
{
	Circle c1(Vector2(0, 0), 50);

	Polygon p1;
	p1.SetPointCount(3);
	p1.SetPoint(0, Vector2(-50, 0));
	p1.SetPoint(1, Vector2(50, 0));
	p1.SetPoint(2, Vector2(0, 50));
	p1.ReCalc();

	auto i = c1.GetIntersects(p1);

	EXPECT_EQ(i.size(), 3);

	EXPECT_EQ(50, i[0].x);
	EXPECT_EQ(0, i[0].y);

	EXPECT_EQ(-50, i[1].x);
	EXPECT_EQ(0, i[1].y);

	EXPECT_EQ(0, i[2].x);
	EXPECT_EQ(50, i[2].y);

	Circle c2(Vector2(0, 0), 150);
	i = c2.GetIntersects(p1);
	EXPECT_EQ(i.size(), 0);

	Polygon p2;
	p2.SetPointCount(3);
	p2.SetPoint(0, Vector2(101, 0));
	p2.SetPoint(1, Vector2(151, 0));
	p2.SetPoint(2, Vector2(126, 50));
	p2.ReCalc();

	i = c1.GetIntersects(p2);
	EXPECT_EQ(i.size(), 0);
}

TEST(Circle, GetDisplacementSegment)
{
	Circle c(Vector2(0, 0), 50);

	Segment s1(Vector2(0, 0), Vector2(0, 50));
	auto d = c.GetDisplacement(s1);
	EXPECT_FLOAT_EQ(51, d.Length());
	EXPECT_FALSE(c.Overlaps(mSegment(s1, d)));

	Segment s2(Vector2(25, 0), Vector2(25, 50));
	d = c.GetDisplacement(s2);
	EXPECT_FLOAT_EQ(26, d.Length());
	EXPECT_FALSE(c.Overlaps(mSegment(s2, d)));

	Segment s3(Vector2(51, 0), Vector2(51, 50));
	d = c.GetDisplacement(s3);
	EXPECT_FLOAT_EQ(0, d.Length());
}

TEST(Circle, GetDisplacementCircle)
{
	Circle c1(Vector2(0, 0), 50);

	Circle c2(Vector2(0, 0), 50);
	auto d = c1.GetDisplacement(c2);
	EXPECT_FLOAT_EQ(101, d.Length());
	EXPECT_FALSE(c1.Overlaps(mCircle(c2, d)));

	Circle c3(Vector2(25, 0), 50);
	d = c1.GetDisplacement(c3);
	EXPECT_FLOAT_EQ(76, d.Length());
	EXPECT_FALSE(c1.Overlaps(mCircle(c3, d)));

	Circle c4(Vector2(101, 0), 50);
	d = c1.GetDisplacement(c4);
	EXPECT_FLOAT_EQ(0, d.Length());
}

TEST(Circle, GetDisplacementPolygon)
{
	Circle c(Vector2(0, 0), 50);

	Polygon p1;
	p1.SetPointCount(3);
	p1.SetPoint(0, Vector2(-50, 0));
	p1.SetPoint(1, Vector2(50, 0));
	p1.SetPoint(2, Vector2(0, 50));
	p1.ReCalc();

	auto d = c.GetDisplacement(p1);
	EXPECT_FLOAT_EQ(51, d.Length());
	EXPECT_FALSE(c.Overlaps(mPolygon(p1, d)));

	Polygon p2;
	p2.SetPointCount(3);
	p2.SetPoint(0, Vector2(-50, 25));
	p2.SetPoint(1, Vector2(50, 25));
	p2.SetPoint(2, Vector2(0, 75));
	p2.ReCalc();

	d = c.GetDisplacement(p2);
	EXPECT_FLOAT_EQ(26, d.Length());
	EXPECT_FALSE(c.Overlaps(mPolygon(p2, d)));

	Polygon p3;
	p3.SetPointCount(3);
	p3.SetPoint(0, Vector2(-50, 51));
	p3.SetPoint(1, Vector2(50, 51));
	p3.SetPoint(2, Vector2(0, 101));
	p3.ReCalc();

	d = c.GetDisplacement(p3);
	EXPECT_FLOAT_EQ(0, d.Length());
}

// Collision is just above funcs rolled so just checking for consistency

TEST(Circle, GetGollisionSegment)
{
	Circle c(Vector2(0, 0), 50);
	Segment s(Vector2(-50, 0), Vector2(50, 0));

	Collision col = c.GetCollision(s);
	EXPECT_EQ(c.Overlaps(s), col.Overlaps());
	EXPECT_EQ(c.Contains(s), col.AcontainsB());
	EXPECT_EQ(s.Contains(c), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = c.GetIntersects(s);

	EXPECT_EQ(iC.size(), iF.size());

	for (unsigned i = 0; i < iC.size(); ++i)
	{
		EXPECT_FLOAT_EQ(iC[i].x, iF[i].x);
		EXPECT_FLOAT_EQ(iC[i].y, iF[i].y);
	}

	auto dC = col.GetDisplacement();
	auto dF = c.GetDisplacement(s);

	EXPECT_FLOAT_EQ(dC.x, dF.x);
	EXPECT_FLOAT_EQ(dC.y, dF.y);
}

TEST(Circle, GetGollisionCircle)
{
	Circle c1(Vector2(0, 0), 50);
	Circle c2(Vector2(25, 25), 50);

	Collision col = c1.GetCollision(c2);
	EXPECT_EQ(c1.Overlaps(c2), col.Overlaps());
	EXPECT_EQ(c1.Contains(c2), col.AcontainsB());
	EXPECT_EQ(c2.Contains(c1), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = c1.GetIntersects(c2);

	EXPECT_EQ(iC.size(), iF.size());

	for (unsigned i = 0; i < iC.size(); ++i)
	{
		EXPECT_FLOAT_EQ(iC[i].x, iF[i].x);
		EXPECT_FLOAT_EQ(iC[i].y, iF[i].y);
	}

	auto dC = col.GetDisplacement();
	auto dF = c1.GetDisplacement(c2);

	EXPECT_FLOAT_EQ(dC.x, dF.x);
	EXPECT_FLOAT_EQ(dC.y, dF.y);
}

TEST(Circle, GetGollisionPolygon)
{
	Circle c(Vector2(0, 0), 50);

	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(0, 50));
	p.ReCalc();

	Collision col = c.GetCollision(p);
	EXPECT_EQ(c.Overlaps(p), col.Overlaps());
	EXPECT_EQ(c.Contains(p), col.AcontainsB());
	EXPECT_EQ(p.Contains(c), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = c.GetIntersects(p);

	EXPECT_EQ(iC.size(), iF.size());

	for (unsigned i = 0; i < iC.size(); ++i)
	{
		EXPECT_FLOAT_EQ(iC[i].x, iF[i].x);
		EXPECT_FLOAT_EQ(iC[i].y, iF[i].y);
	}

	auto dC = col.GetDisplacement();
	auto dF = c.GetDisplacement(p);

	EXPECT_FLOAT_EQ(dC.x, dF.x);
	EXPECT_FLOAT_EQ(dC.y, dF.y);
}

// Double Disbatch test

TEST(Circle, GetGollisionShape)
{
	Shape *c1 = new Circle(Vector2(0, 0), 50);
	Shape *c2 = new Circle(Vector2(25, 25), 50);

	Collision colPtr = c1->GetCollision(*c2);

	Circle A = *dynamic_cast<Circle*>(c1);
	Circle B = *dynamic_cast<Circle*>(c2);

	Collision colObj = A.GetCollision(B);

	EXPECT_EQ(colPtr.Overlaps(), colObj.Overlaps());
	EXPECT_EQ(colPtr.AcontainsB(), colObj.AcontainsB());
	EXPECT_EQ(colPtr.BcontainsA(), colObj.BcontainsA());

	auto iP = colPtr.GetIntersects();
	auto iO = colObj.GetIntersects();

	EXPECT_EQ(iP.size(), iO.size());

	for (unsigned i = 0; i < iP.size(); ++i)
	{
		EXPECT_FLOAT_EQ(iP[i].x, iO[i].x);
		EXPECT_FLOAT_EQ(iP[i].y, iO[i].y);
	}

	EXPECT_FLOAT_EQ(colPtr.GetDisplacement().x, colObj.GetDisplacement().x);
	EXPECT_FLOAT_EQ(colPtr.GetDisplacement().y, colObj.GetDisplacement().y);
}
