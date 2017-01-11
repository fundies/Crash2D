#include "helper_func.hpp"

#include <gtest/gtest.h>
#include <cmath>

TEST(Segment, DefaultConstructor)
{
	Segment s;

	EXPECT_EQ(0	, s.GetPoint(0).x);
	EXPECT_EQ(0, s.GetPoint(0).y);

	EXPECT_EQ(0, s.GetPoint(1).x);
	EXPECT_EQ(0, s.GetPoint(1).y);

	EXPECT_FLOAT_EQ(0, s.GetSlope());

	EXPECT_FLOAT_EQ(0, s.GetCenter().x);
	EXPECT_FLOAT_EQ(0, s.GetCenter().y);
}

TEST(Segment, Constructor2Points)
{
	Segment s(Vector2(0, 0), Vector2(10, 10));

	EXPECT_EQ(0	, s.GetPoint(0).x);
	EXPECT_EQ(0, s.GetPoint(0).y);

	EXPECT_EQ(10, s.GetPoint(1).x);
	EXPECT_EQ(10, s.GetPoint(1).y);

	EXPECT_FLOAT_EQ(1, s.GetSlope());

	EXPECT_EQ(5, s.GetCenter().x);
	EXPECT_EQ(5, s.GetCenter().y);
}

TEST(Segment, SetPoint)
{
	Segment s;

	s.SetPoint(0, Vector2(9, 6));
	s.SetPoint(1, Vector2(-3, 4));
	s.ReCalc();

	EXPECT_EQ(9	, s.GetPoint(0).x);
	EXPECT_EQ(6, s.GetPoint(0).y);

	EXPECT_EQ(-3, s.GetPoint(1).x);
	EXPECT_EQ(4, s.GetPoint(1).y);

	EXPECT_FLOAT_EQ(1.f / 6.f, s.GetSlope());

	EXPECT_EQ(3, s.GetCenter().x);
	EXPECT_EQ(5, s.GetCenter().y);
}

TEST(Segment, DistancePoint)
{
	Segment s(Vector2(2, 2), Vector2(10, 5));
	Vector2 v(0, 0);

	// Outside
	//EXPECT_FLOAT_EQ(2 * std::sqrt(2), s.DistancePoint(v));

	// Below
	v = Vector2(4, 3);
	EXPECT_FLOAT_EQ(2 / std::sqrt(73), s.DistancePoint(v));

	//Above
	v = Vector2(3, 4);
	EXPECT_FLOAT_EQ(13 / std::sqrt(73), s.DistancePoint(v));

}

TEST(Segment, SignedDistancePoint)
{
	Segment s(Vector2(2, 2), Vector2(10, 5));
	Vector2 v(0, 0);

	// Outside
	//EXPECT_FLOAT_EQ(2 * std::sqrt(2), s.SignedDistancePoint(v));

	// On
	v = Vector2(10, 5);
	EXPECT_FLOAT_EQ(0, s.SignedDistancePoint(v));

	v = Vector2(2, 2);
	EXPECT_FLOAT_EQ(0, s.SignedDistancePoint(v));

	// Below
	v = Vector2(4, 3);
	EXPECT_FLOAT_EQ(-2 / std::sqrt(73), s.SignedDistancePoint(v));

	//Above
	v = Vector2(3, 4);
	EXPECT_FLOAT_EQ(-13 / std::sqrt(73), s.SignedDistancePoint(v));

	Segment s2(Vector2(0, 0), Vector2(0, 4));
	EXPECT_FLOAT_EQ(2, s2.SignedDistancePoint(Vector2(2, 2)));
	EXPECT_FLOAT_EQ(-2, s2.SignedDistancePoint(Vector2(-2, 2)));

}

TEST(Segment, GetLength)
{
	Vector2 a(0, 0);
	Vector2 b(10, 10);

	Segment s(a, b);

	EXPECT_FLOAT_EQ(10 * std::sqrt(2), s.GetLength());
}

TEST(Segment, GetNearestPoint)
{
	Segment s(Vector2(0, 0), Vector2(100, 0));

	Vector2 p = s.GetNearestPoint(Vector2(-10, 0));
	EXPECT_FLOAT_EQ(0, p.x);
	EXPECT_FLOAT_EQ(0, p.y);

	p = s.GetNearestPoint(Vector2(110, 0));
	EXPECT_FLOAT_EQ(100, p.x);
	EXPECT_FLOAT_EQ(0, p.y);

	p = s.GetNearestPoint(Vector2(50, 0));
	EXPECT_FLOAT_EQ(50, p.x);
	EXPECT_FLOAT_EQ(0, p.y);
}

TEST(Segment, IsPerpendicular)
{
	Segment s1(Vector2(0, 0), Vector2(10, 0));
	Segment s2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(s1.IsPerpendicular(s2));

	s1 = Segment(Vector2(0, 0), Vector2(4, 4));
	s2 = Segment(Vector2(0, 0), Vector2(4, -4));

	EXPECT_TRUE(s1.IsPerpendicular(s2));

	s2 = Segment(Vector2(0, 0), Vector2(-4, -4));

	EXPECT_FALSE(s1.IsPerpendicular(s2));
}

TEST(Segment, IsParallel)
{
	Segment s1(Vector2(5, 5), Vector2(5, -5));
	Segment s2(Vector2(4, 4), Vector2(4, -4));

	EXPECT_TRUE(s1.IsParallel(s2));

	s1 = Segment(Vector2(0, 0), Vector2(4, 4));
	s2 = Segment(Vector2(0, 0), Vector2(-4, -4));

	EXPECT_TRUE(s1.IsParallel(s2));

	s2 = Segment(Vector2(0, 0), Vector2(-4, 4));

	EXPECT_FALSE(s1.IsParallel(s2));
}

TEST(Segment, Project)
{
	Segment s(Vector2(0, 0), Vector2(100, 100));
	Projection p = s.Project(Axis(5, 5));

	EXPECT_FLOAT_EQ(0, p.min);
	EXPECT_FLOAT_EQ(1000, p.max);
}

TEST(Segment, ProjectShapeAxis)
{
	Segment s(Vector2(0, 0), Vector2(100, 100));
	Projection p = s.Project(s, Axis(5, 5));

	EXPECT_FLOAT_EQ(0, p.min);
	EXPECT_FLOAT_EQ(1000, p.max);
}

TEST(Segment, ContainsPoint)
{
	Segment s(Vector2(0, 0), Vector2(10, 10));

	EXPECT_TRUE(s.Contains(Vector2(5, 5)));
	EXPECT_FALSE(s.Contains(Vector2(-1, -1)));
	EXPECT_FALSE(s.Contains(Vector2(0, 2)));
}

TEST(Segment, ContainsSegment)
{
	Segment s1(Vector2(-50, 0), Vector2(50, 0));
	Segment s2(Vector2(0, 0), Vector2(50, 0));

	EXPECT_TRUE(s1.Contains(s2));

	s2.SetPoint(1, Vector2(51, 0));

	EXPECT_FALSE(s1.Contains(s2));
}

TEST(Segment, ContainsCircle)
{
	Segment s(Vector2(-50, 0), Vector2(50, 0));
	Circle c(Vector2(0, 0), 5);

	EXPECT_FALSE(s.Contains(c));
}

TEST(Segment, ContainsPolygon)
{
	Segment s(Vector2(-50, 0), Vector2(50, 0));

	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	EXPECT_FALSE(s.Contains(p));
}

TEST(Segment, OverlapsSegment)
{
	Segment s1(Vector2(50, 0), Vector2(100, 0));
	Segment s2(Vector2(75, -20), Vector2(75, 50));

	EXPECT_TRUE(s1.Overlaps(s2));

	s2.SetPoint(1, Vector2(75, -50));
	s2.ReCalc();

	EXPECT_FALSE(s1.Overlaps(s2));
}

TEST(Segment, OverlapsCircle)
{
	Segment s(Vector2(50, 0), Vector2(100, 0));
	Circle c(Vector2(0, 0), 50);

	EXPECT_TRUE(s.Overlaps(c));

	s.SetPoint(0, Vector2(51, 0));
	s.ReCalc();

	EXPECT_FALSE(s.Overlaps(c));
}

TEST(Segment, OverlapsPolygon)
{
	Segment s(Vector2(50, 0), Vector2(100, 0));

	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	EXPECT_TRUE(s.Overlaps(p));

	s.SetPoint(0, Vector2(51, 0));
	s.ReCalc();

	EXPECT_FALSE(s.Overlaps(p));
}

TEST(Segment, GetIntersectsSegment)
{
	Segment s1(Vector2(50, 0), Vector2(100, 0));
	Segment s2(Vector2(75, -20), Vector2(75, 50));

	auto i = s1.GetIntersects(s2);
	EXPECT_EQ(1, i.size());

	EXPECT_EQ(75, i[0].x);
	EXPECT_EQ(0, i[0].y);

	s2.SetPoint(1, Vector2(75, -50));
	s2.ReCalc();

	i = s1.GetIntersects(s2);
	EXPECT_EQ(0, i.size());
}

TEST(Segment, GetIntersectsCircle)
{
	Circle c(Vector2(0, 0), 50);
	Segment s(Vector2(-50, 0), Vector2(50, 0));

	auto i = s.GetIntersects(c);

	EXPECT_EQ(i.size(), 2);

	EXPECT_EQ(50, i[0].x);
	EXPECT_EQ(0, i[0].y);

	EXPECT_EQ(-50, i[1].x);
	EXPECT_EQ(0, i[1].y);

	s = Segment(Vector2(-50, 50), Vector2(50, 50));
	i = s.GetIntersects(c);

	EXPECT_EQ(i.size(), 1);
	EXPECT_EQ(0, i[0].x);
	EXPECT_EQ(50, i[0].y);

	s = Segment(Vector2(-50, 51), Vector2(50, 51));
	i = s.GetIntersects(c);
	EXPECT_EQ(i.size(), 0);
}

TEST(Segment, GetIntersectsPolygon)
{
	Segment s(Vector2(-51, 0), Vector2(51, 0));

	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	auto i = s.GetIntersects(p);

	EXPECT_EQ(i.size(), 2);

	EXPECT_EQ(50, i[0].x);
	EXPECT_EQ(0, i[0].y);

	EXPECT_EQ(-50, i[1].x);
	EXPECT_EQ(0, i[1].y);

	s = Segment(Vector2(-50, 0), Vector2(-50, 50));
	i = s.GetIntersects(p);

	EXPECT_EQ(i.size(), 1);
	EXPECT_EQ(-50, i[0].x);
	EXPECT_EQ(0, i[0].y);

	s = Segment(Vector2(-50, 51), Vector2(50, 51));
	i = s.GetIntersects(p);
	EXPECT_EQ(i.size(), 0);
}

TEST(Segment, GetDisplacementSegment)
{
	Segment s1(Vector2(50, 0), Vector2(100, 0));
	Segment s2(Vector2(75, -20), Vector2(75, 50));

	auto d = s1.GetDisplacement(s2);
	EXPECT_FLOAT_EQ(21, d.Length());
	EXPECT_FALSE(s1.Overlaps(mSegment(s2, d)));

	Segment s3(Vector2(101, 0), Vector2(151, 0));
	d = s1.GetDisplacement(s3);
	EXPECT_FLOAT_EQ(0, d.Length());
}

TEST(Segment, GetDisplacementCircle)
{
	Circle c(Vector2(0, 0), 50);

	Segment s1(Vector2(0, 0), Vector2(0, 50));
	auto d = s1.GetDisplacement(c);
	EXPECT_FLOAT_EQ(51, d.Length());
	EXPECT_FALSE(s1.Overlaps(mCircle(c, d)));

	Segment s2(Vector2(25, 0), Vector2(25, 50));
	d = s2.GetDisplacement(c);
	EXPECT_FLOAT_EQ(26, d.Length());
	EXPECT_FALSE(s2.Overlaps(mCircle(c, d)));

	Segment s3(Vector2(51, 0), Vector2(51, 50));
	d = s3.GetDisplacement(c);
	EXPECT_FLOAT_EQ(0, d.Length());
}

TEST(Segment, GetDisplacementPolygon)
{
	Polygon p;
	p.SetPointCount(4);
	p.SetPoint(0, Vector2(-50, -50));
	p.SetPoint(1, Vector2(50, -50));
	p.SetPoint(2, Vector2(50, 50));
	p.SetPoint(3, Vector2(-50, 50));
	p.ReCalc();

	Segment s1(Vector2(0, 0), Vector2(0, 50));
	auto d = s1.GetDisplacement(p);
	EXPECT_FLOAT_EQ(51, d.Length());
	EXPECT_FALSE(s1.Overlaps(mPolygon(p, d)));

	Segment s2(Vector2(25, 0), Vector2(25, 50));
	d = s2.GetDisplacement(p);
	EXPECT_FLOAT_EQ(26, d.Length());
	EXPECT_FALSE(s2.Overlaps(mPolygon(p, d)));

	Segment s3(Vector2(51, 0), Vector2(51, 50));
	d = s3.GetDisplacement(p);
	EXPECT_FLOAT_EQ(0, d.Length());
}

// Collision is just above funcs rolled so just checking for consistency

TEST(Segment, GetGollisionSegment)
{
	Segment s1(Vector2(-50, 0), Vector2(50, 0));
	Segment s2(Vector2(0, -50), Vector2(50, 30));

	Collision col = s1.GetCollision(s2);
	EXPECT_EQ(s1.Overlaps(s2), col.Overlaps());
	EXPECT_EQ(s1.Contains(s2), col.AcontainsB());
	EXPECT_EQ(s2.Contains(s1), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = s1.GetIntersects(s2);

	EXPECT_EQ(iC.size(), iF.size());

	for (unsigned i = 0; i < iC.size(); ++i)
	{
		EXPECT_FLOAT_EQ(iC[i].x, iF[i].x);
		EXPECT_FLOAT_EQ(iC[i].y, iF[i].y);
	}

	auto dC = col.GetDisplacement();
	auto dF = s1.GetDisplacement(s2);

	EXPECT_FLOAT_EQ(dC.x, dF.x);
	EXPECT_FLOAT_EQ(dC.y, dF.y);
}

TEST(Segment, GetGollisionCircle)
{
	Circle c(Vector2(0, 0), 50);
	Segment s(Vector2(-50, 0), Vector2(50, 0));

	Collision col = s.GetCollision(c);
	EXPECT_EQ(s.Overlaps(c), col.Overlaps());
	EXPECT_EQ(s.Contains(c), col.AcontainsB());
	EXPECT_EQ(c.Contains(s), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = s.GetIntersects(c);

	EXPECT_EQ(iC.size(), iF.size());

	for (unsigned i = 0; i < iC.size(); ++i)
	{
		EXPECT_FLOAT_EQ(iC[i].x, iF[i].x);
		EXPECT_FLOAT_EQ(iC[i].y, iF[i].y);
	}

	auto dC = col.GetDisplacement();
	auto dF = s.GetDisplacement(c);

	EXPECT_FLOAT_EQ(dC.x, dF.x);
	EXPECT_FLOAT_EQ(dC.y, dF.y);
}

TEST(Segment, GetGollisionPolygon)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(0, 50));
	p.ReCalc();

	Segment s(Vector2(-50, 0), Vector2(50, 0));

	Collision col = s.GetCollision(p);
	EXPECT_EQ(s.Overlaps(p), col.Overlaps());
	EXPECT_EQ(s.Contains(p), col.AcontainsB());
	EXPECT_EQ(p.Contains(s), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = s.GetIntersects(p);

	EXPECT_EQ(iC.size(), iF.size());

	for (unsigned i = 0; i < iC.size(); ++i)
	{
		EXPECT_FLOAT_EQ(iC[i].x, iF[i].x);
		EXPECT_FLOAT_EQ(iC[i].y, iF[i].y);
	}

	auto dC = col.GetDisplacement();
	auto dF = s.GetDisplacement(p);

	EXPECT_FLOAT_EQ(dC.x, dF.x);
	EXPECT_FLOAT_EQ(dC.y, dF.y);
}

// Double Disbatch test

TEST(Segment, GetGollisionShape)
{
	Shape *a = new Segment(Vector2(400, 300), Vector2(500, 300));
	Shape *b = new Segment(Vector2(480, 250), Vector2(480, 350));

	Collision colPtr = a->GetCollision(*b);

	Segment A = *dynamic_cast<Segment*>(a);
	Segment B = *dynamic_cast<Segment*>(b);

	Collision colObj = A.GetCollision(B);

	EXPECT_EQ(colPtr.Overlaps(), colObj.Overlaps());
	EXPECT_EQ(colPtr.AcontainsB(), colObj.AcontainsB());
	EXPECT_EQ(colPtr.BcontainsA(), colObj.BcontainsA());

	auto iP = colPtr.GetIntersects();
	auto iO = colObj.GetIntersects();

	EXPECT_EQ(iP.size(), 1);
	EXPECT_EQ(iP.size(), iO.size());

	for (unsigned i = 0; i < iP.size(); ++i)
	{
		auto it = std::find(std::begin(iP), std::end(iP), iO[i]);
		EXPECT_TRUE(it != std::end(iP));
	}

	EXPECT_FLOAT_EQ(colPtr.GetDisplacement().x, colObj.GetDisplacement().x);
	EXPECT_FLOAT_EQ(colPtr.GetDisplacement().y, colObj.GetDisplacement().y);
}
