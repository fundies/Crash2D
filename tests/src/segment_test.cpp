#include "helper.hpp"

TEST(Segment, DefaultConstructor)
{
	Segment s;

	ARE_EQ(0, s.GetPoint(0).x);
	ARE_EQ(0, s.GetPoint(0).y);

	ARE_EQ(0, s.GetPoint(1).x);
	ARE_EQ(0, s.GetPoint(1).y);

	ARE_EQ(0, s.GetSlope());

	ARE_EQ(0, s.GetCenter().x);
	ARE_EQ(0, s.GetCenter().y);
}

TEST(Segment, Constructor2Points)
{
	Segment s(Vector2(0, 0), Vector2(10, 10));

	ARE_EQ(0, s.GetPoint(0).x);
	ARE_EQ(0, s.GetPoint(0).y);

	ARE_EQ(10, s.GetPoint(1).x);
	ARE_EQ(10, s.GetPoint(1).y);

	ARE_EQ(1, s.GetSlope());

	ARE_EQ(5, s.GetCenter().x);
	ARE_EQ(5, s.GetCenter().y);
}

TEST(Segment, SetPoint)
{
	Segment s;

	s.SetPoint(0, Vector2(9, 6));
	s.SetPoint(1, Vector2(-3, 4));
	s.ReCalc();

	ARE_EQ(9, s.GetPoint(0).x);
	ARE_EQ(6, s.GetPoint(0).y);

	ARE_EQ(-3, s.GetPoint(1).x);
	ARE_EQ(4, s.GetPoint(1).y);

	ARE_EQ(1.f / 6.f, s.GetSlope());

	ARE_EQ(3, s.GetCenter().x);
	ARE_EQ(5, s.GetCenter().y);
}

TEST(Segment, DistancePoint)
{
	Segment s(Vector2(2, 2), Vector2(10, 5));
	Vector2 v(0, 0);

	// Outside
	//ARE_EQ(2 * std::sqrt(2), s.DistancePoint(v));

	// Below
	v = Vector2(4, 3);
	ARE_EQ(2 / std::sqrt(73), s.DistancePoint(v));

	//Above
	v = Vector2(3, 4);
	ARE_EQ(13 / std::sqrt(73), s.DistancePoint(v));

}

TEST(Segment, SignedDistancePoint)
{
	Segment s(Vector2(2, 2), Vector2(10, 5));
	Vector2 v(0, 0);

	// Outside
	//ARE_EQ(2 * std::sqrt(2), s.SignedDistancePoint(v));

	// On
	v = Vector2(10, 5);
	ARE_EQ(0, s.SignedDistancePoint(v));

	v = Vector2(2, 2);
	ARE_EQ(0, s.SignedDistancePoint(v));

	// Below
	v = Vector2(4, 3);
	ARE_EQ(-2 / std::sqrt(73), s.SignedDistancePoint(v));

	//Above
	v = Vector2(3, 4);
	ARE_EQ(-13 / std::sqrt(73), s.SignedDistancePoint(v));

	Segment s2(Vector2(0, 0), Vector2(0, 4));
	ARE_EQ(2, s2.SignedDistancePoint(Vector2(2, 2)));
	ARE_EQ(-2, s2.SignedDistancePoint(Vector2(-2, 2)));

}

TEST(Segment, GetLength)
{
	Vector2 a(0, 0);
	Vector2 b(10, 10);

	Segment s(a, b);

	ARE_EQ(10 * std::sqrt(2), s.GetLength());
}

TEST(Segment, GetNearestPoint)
{
	Segment s(Vector2(0, 0), Vector2(100, 0));

	Vector2 p = s.GetNearestPoint(Vector2(-10, 0));
	ARE_EQ(0, p.x);
	ARE_EQ(0, p.y);

	p = s.GetNearestPoint(Vector2(110, 0));
	ARE_EQ(100, p.x);
	ARE_EQ(0, p.y);

	p = s.GetNearestPoint(Vector2(50, 0));
	ARE_EQ(50, p.x);
	ARE_EQ(0, p.y);
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

	ARE_EQ(0, p.min);
	ARE_EQ(1000, p.max);
}

TEST(Segment, ProjectShapeAxis)
{
	Segment s(Vector2(0, 0), Vector2(100, 100));
	Projection p = s.Project(s, Axis(5, 5));

	ARE_EQ(0, p.min);
	ARE_EQ(1000, p.max);
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

TEST(Segment, IsInsideSegment)
{
	Segment s1(Vector2(0, 0), Vector2(50, 0));
	Segment s2(Vector2(10, 0), Vector2(50, 0));

	EXPECT_FALSE(s1.IsInside(s2));
	EXPECT_TRUE(s2.IsInside(s1));
}

TEST(Segment, IsInsideCircle)
{
	Segment s(Vector2(-50, 0), Vector2(50, 0));
	Circle c(Vector2(0, 0), 50);

	EXPECT_TRUE(s.IsInside(c));
}

TEST(Segment, IsInsidePolygon)
{
	Segment s(Vector2(-50, 0), Vector2(50, 0));

	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	EXPECT_TRUE(s.IsInside(p));
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
	Segment s(Vector2(49, 0), Vector2(100, 0));
	Circle c(Vector2(0, 0), 50);

	EXPECT_TRUE(s.Overlaps(c));

	s.SetPoint(0, Vector2(50, 0));
	s.ReCalc();

	EXPECT_FALSE(s.Overlaps(c));
}

TEST(Segment, OverlapsPolygon)
{
	Segment s(Vector2(49, 1), Vector2(100, 0));

	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	EXPECT_TRUE(s.Overlaps(p));

	s.SetPoint(0, Vector2(50, 0));
	s.ReCalc();

	EXPECT_FALSE(s.Overlaps(p));
}

TEST(Segment, GetIntersectsSegment)
{
	Segment s1(Vector2(50, 0), Vector2(100, 0));
	Segment s2(Vector2(75, -20), Vector2(75, 50));

	auto i = s1.GetIntersects(s2);
	ARE_EQ(1, i.size());

	ARE_EQ(75, i[0].x);
	ARE_EQ(0, i[0].y);

	s2.SetPoint(1, Vector2(75, -50));
	s2.ReCalc();

	i = s1.GetIntersects(s2);
	ARE_EQ(0, i.size());
}

TEST(Segment, GetIntersectsCircle)
{
	Circle c(Vector2(0, 0), 50);
	Segment s(Vector2(-50, 0), Vector2(50, 0));

	auto i = s.GetIntersects(c);

	ARE_EQ(i.size(), 2);

	ARE_EQ(50, i[0].x);
	ARE_EQ(0, i[0].y);

	ARE_EQ(-50, i[1].x);
	ARE_EQ(0, i[1].y);

	s = Segment(Vector2(-50, 50), Vector2(50, 50));
	i = s.GetIntersects(c);

	ARE_EQ(i.size(), 1);
	ARE_EQ(0, i[0].x);
	ARE_EQ(50, i[0].y);

	s = Segment(Vector2(-50, 51), Vector2(50, 51));
	i = s.GetIntersects(c);
	ARE_EQ(i.size(), 0);
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

	ARE_EQ(i.size(), 2);

	ARE_EQ(50, i[0].x);
	ARE_EQ(0, i[0].y);

	ARE_EQ(-50, i[1].x);
	ARE_EQ(0, i[1].y);

	s = Segment(Vector2(-50, 0), Vector2(-50, 50));
	i = s.GetIntersects(p);

	ARE_EQ(i.size(), 1);
	ARE_EQ(-50, i[0].x);
	ARE_EQ(0, i[0].y);

	s = Segment(Vector2(-50, 51), Vector2(50, 51));
	i = s.GetIntersects(p);
	ARE_EQ(i.size(), 0);
}

TEST(Segment, GetDisplacementSegment)
{
	Segment s1(Vector2(50, 0), Vector2(100, 0));
	Segment s2(Vector2(75, -20), Vector2(75, 50));

	auto d = s1.GetDisplacement(s2);
	ARE_EQ(20, d.Length());
	EXPECT_FALSE(s1.Overlaps(mSegment(s2, d+1)));

	Segment s3(Vector2(101, 0), Vector2(151, 0));
	d = s1.GetDisplacement(s3);
	ARE_EQ(0, d.Length());
}

TEST(Segment, GetDisplacementCircle)
{
	Circle c(Vector2(0, 0), 50);

	Segment s1(Vector2(0, 0), Vector2(0, 50));
	auto d = s1.GetDisplacement(c);
	ARE_EQ(50, d.Length());
	EXPECT_FALSE(s1.Overlaps(mCircle(c, d)));

	Segment s2(Vector2(25, 0), Vector2(25, 50));
	d = s2.GetDisplacement(c);
	ARE_EQ(25, d.Length());
	EXPECT_FALSE(s2.Overlaps(mCircle(c, d)));

	Segment s3(Vector2(51, 0), Vector2(51, 50));
	d = s3.GetDisplacement(c);
	ARE_EQ(0, d.Length());
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
	ARE_EQ(50, d.Length());
	EXPECT_FALSE(s1.Overlaps(mPolygon(p, d)));

	Segment s2(Vector2(25, 0), Vector2(25, 50));
	d = s2.GetDisplacement(p);
	ARE_EQ(25, d.Length());
	EXPECT_FALSE(s2.Overlaps(mPolygon(p, d)));

	Segment s3(Vector2(51, 0), Vector2(51, 50));
	d = s3.GetDisplacement(p);
	ARE_EQ(0, d.Length());
}

// Collision is just above funcs rolled so just checking for consistency

TEST(Segment, GetGollisionSegment)
{
	Segment s1(Vector2(-50, 0), Vector2(50, 0));
	Segment s2(Vector2(0, -50), Vector2(50, 30));

	Collision col = s1.GetCollision(s2);
	ARE_EQ(s1.Overlaps(s2), col.Overlaps());
	ARE_EQ(s1.Contains(s2), col.AcontainsB());
	ARE_EQ(s2.Contains(s1), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = s1.GetIntersects(s2);

	ARE_EQ(iC.size(), iF.size());

	ARE_EQ(iC[0].x, iF[0].x);
	ARE_EQ(iC[0].y, iF[0].y);

	auto dC = col.GetDisplacement();
	auto dF = s1.GetDisplacement(s2);

	ARE_EQ(dC.x, dF.x);
	ARE_EQ(dC.y, dF.y);
}

TEST(Segment, GetGollisionCircle)
{
	Circle c(Vector2(0, 0), 50);
	Segment s(Vector2(-50, 10), Vector2(50, 10));

	Collision col = s.GetCollision(c);
	ARE_EQ(s.Overlaps(c), col.Overlaps());
	ARE_EQ(s.Contains(c), col.AcontainsB());
	ARE_EQ(c.Contains(s), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = s.GetIntersects(c);

	ARE_EQ(iC.size(), iF.size());

	EXPECT_TRUE(vectorEQ(iF, iC));

	auto dC = col.GetDisplacement();
	auto dF = s.GetDisplacement(c);

	ARE_EQ(dC.x, dF.x);
	ARE_EQ(dC.y, dF.y);
}

TEST(Segment, GetGollisionPolygon)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	Segment s(Vector2(-49, 1), Vector2(50, 0));

	Collision col = s.GetCollision(p);
	ARE_EQ(s.Overlaps(p), col.Overlaps());
	ARE_EQ(s.Contains(p), col.AcontainsB());
	ARE_EQ(p.Contains(s), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = s.GetIntersects(p);

	ARE_EQ(iC.size(), iF.size());

	EXPECT_TRUE(vectorEQ(iF, iC));

	auto dC = col.GetDisplacement();
	auto dF = s.GetDisplacement(p);

	ARE_EQ(dC.x, dF.x);
	ARE_EQ(dC.y, dF.y);
}

// Double Disbatch test

TEST(Segment, ContainsShape)
{
	ShapePtr aP(new Segment(Vector2(400, 350), Vector2(500, 350)));
	ShapePtr bP(new Segment(Vector2(420, 350), Vector2(480, 350)));

	Segment aO = *dynamic_cast<Segment*>(aP.get());
	Segment bO = *dynamic_cast<Segment*>(bP.get());

	EXPECT_EQ(aP->Contains(*bP), aO.Contains(bO));

	EXPECT_TRUE(aP->Contains(*bP));
	EXPECT_FALSE(bP->Contains(*aP));
}

TEST(Segment, IsInsideShape)
{
	ShapePtr aP(new Segment(Vector2(400, 350), Vector2(500, 350)));
	ShapePtr bP(new Segment(Vector2(420, 350), Vector2(480, 350)));

	Segment aO = *dynamic_cast<Segment*>(aP.get());
	Segment bO = *dynamic_cast<Segment*>(bP.get());

	EXPECT_EQ(aP->IsInside(*bP), aO.IsInside(bO));

	EXPECT_FALSE(aP->IsInside(*bP));
	EXPECT_TRUE(bP->IsInside(*aP));
}

TEST(Segment, OverlapsShape)
{
	ShapePtr aP(new Segment(Vector2(400, 300), Vector2(500, 300)));
	ShapePtr bP(new Segment(Vector2(480, 250), Vector2(480, 350)));

	Segment aO = *dynamic_cast<Segment*>(aP.get());
	Segment bO = *dynamic_cast<Segment*>(bP.get());

	EXPECT_EQ(aP->Overlaps(*bP), aO.Overlaps(bO));

	EXPECT_TRUE(aP->Overlaps(*bP));
}

TEST(Segment, GetIntersectsShape)
{
	ShapePtr aP(new Segment(Vector2(400, 300), Vector2(500, 300)));
	ShapePtr bP(new Segment(Vector2(480, 250), Vector2(480, 350)));

	Segment aO = *dynamic_cast<Segment*>(aP.get());
	Segment bO = *dynamic_cast<Segment*>(bP.get());

	EXPECT_EQ(aP->GetIntersects(*bP), aO.GetIntersects(bO));

	auto i = aP->GetIntersects(*bP);

	ARE_EQ(1, i.size());
	ARE_EQ(480, i[0].x);
	ARE_EQ(300, i[0].y);
}

TEST(Segment, GetDisplacementShape)
{
	ShapePtr aP(new Segment(Vector2(400, 300), Vector2(500, 300)));
	ShapePtr bP(new Segment(Vector2(480, 250), Vector2(480, 350)));

	Segment aO = *dynamic_cast<Segment*>(aP.get());
	Segment bO = *dynamic_cast<Segment*>(bP.get());

	auto dP = aP->GetDisplacement(*bP);
	auto dO = aO.GetDisplacement(bO);

	EXPECT_EQ(dP.x, dO.x);
	EXPECT_EQ(dP.y, dO.y);

	ARE_EQ(20, dP.x);
	ARE_EQ(0, dP.y);
}

TEST(Segment, GetGollisionShape)
{
	ShapePtr aP(new Segment(Vector2(400, 300), Vector2(500, 300)));
	ShapePtr bP(new Segment(Vector2(480, 250), Vector2(480, 350)));

	Segment aO = *dynamic_cast<Segment*>(aP.get());
	Segment bO = *dynamic_cast<Segment*>(bP.get());

	Collision colPtr = aP->GetCollision(*bP);
	Collision colObj = aO.GetCollision(bO);

	ARE_EQ(colPtr.Overlaps(), colObj.Overlaps());
	ARE_EQ(colPtr.AcontainsB(), colObj.AcontainsB());
	ARE_EQ(colPtr.BcontainsA(), colObj.BcontainsA());

	auto iP = colPtr.GetIntersects();
	auto iO = colObj.GetIntersects();

	ARE_EQ(iP.size(), 1);
	ARE_EQ(iP.size(), iO.size());

	ARE_EQ(480, iP[0].x);
	ARE_EQ(300, iP[0].y);

	ARE_EQ(colPtr.GetDisplacement().x, colObj.GetDisplacement().x);
	ARE_EQ(colPtr.GetDisplacement().y, colObj.GetDisplacement().y);
}
