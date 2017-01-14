#include "helper_func.hpp"

#include <cmath>

TEST(Polygon, DefaultConstructor)
{
	Polygon p;

	ARE_EQ(0, p.GetPointCount());
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
	ARE_EQ(3, axes.size());

	ARE_EQ(-1 / std::sqrt(2), axes[0].x);
	ARE_EQ(1 / std::sqrt(2), axes[0].y);

	ARE_EQ(0, axes[1].x);
	ARE_EQ(-1, axes[1].y);

	ARE_EQ(1 / std::sqrt(5), axes[2].x);
	ARE_EQ(2 / std::sqrt(5), axes[2].y);
}

TEST(Polygon, GetCenter)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(3, 0));
	p.SetPoint(1, Vector2(6, 3));
	p.SetPoint(2, Vector2(-3, 3));
	p.ReCalc();

	ARE_EQ(2, p.GetCenter().x);
	ARE_EQ(2, p.GetCenter().y);
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
	ARE_EQ(-1 / std::sqrt(2) * 3, pj.min);
	ARE_EQ(1 / std::sqrt(2) * 6, pj.max);

	pj = p.Project(axes[1]);
	ARE_EQ(-3, pj.min);
	ARE_EQ(0, pj.max);

	pj = p.Project(axes[2]);
	ARE_EQ(1 / std::sqrt(5) * 3, pj.min);
	ARE_EQ(2 / std::sqrt(5) * 6, pj.max);
}

TEST(Polygon, ProjectShapeAxis)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(3, 0));
	p.SetPoint(1, Vector2(6, 3));
	p.SetPoint(2, Vector2(-3, 3));
	p.ReCalc();

	AxesVec axes = p.GetAxes();
	Projection pj = p.Project(p, axes[0]);
	ARE_EQ(-1 / std::sqrt(2) * 3, pj.min);
	ARE_EQ(1 / std::sqrt(2) * 6, pj.max);
}

TEST(Polygon, ContainsPoint)
{
	Polygon a;
	a.SetPointCount(3);
	a.SetPoint(0, Vector2(-50, 0));
	a.SetPoint(1, Vector2(50, 0));
	a.SetPoint(2, Vector2(25, 50));
	a.ReCalc();

	EXPECT_TRUE(a.Contains(Vector2(-50, 0)));
	EXPECT_TRUE(a.Contains(Vector2(25, 25)));
	EXPECT_FALSE(a.Contains(Vector2(25, 51)));

	Polygon b;
	b.SetPointCount(4);
	b.SetPoint(0, Vector2(-50, 0));
	b.SetPoint(1, Vector2(50, 0));
	b.SetPoint(2, Vector2(50, 50));
	b.SetPoint(3, Vector2(0, 50));
	b.ReCalc();

	EXPECT_TRUE(b.Contains(Vector2(25, 25)));
	EXPECT_FALSE(b.Contains(Vector2(51, 51)));
}

TEST(Polygon, ContainsSegment)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	Segment s(Vector2(-50, 0), Vector2(50, 0));

	EXPECT_TRUE(p.Contains(s));

	s.SetPoint(1, Vector2(51, 0));

	EXPECT_FALSE(p.Contains(s));
}

TEST(Polygon, ContainsCircle)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	Circle c1(Vector2(25, 25), 5);
	Circle c2(Vector2(51, 51), 5);

	EXPECT_TRUE(p.Contains(c1));
	EXPECT_FALSE(p.Contains(c2));
}

TEST(Polygon, ContainsPolygon)
{
	Polygon a;
	a.SetPointCount(3);
	a.SetPoint(0, Vector2(-50, 0));
	a.SetPoint(1, Vector2(50, 0));
	a.SetPoint(2, Vector2(25, 50));
	a.ReCalc();

	Polygon b;
	b.SetPointCount(3);
	b.SetPoint(0, Vector2(-25, 5));
	b.SetPoint(1, Vector2(25, 5));
	b.SetPoint(2, Vector2(12.5, 25));
	b.ReCalc();

	EXPECT_TRUE(a.Contains(b));
	EXPECT_FALSE(b.Contains(a));
}

TEST(Polygon, IsInsideSegment)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	Segment s(Vector2(-50, 0), Vector2(50, 0));

	EXPECT_FALSE(p.IsInside(s));
}

TEST(Polygon, IsInsideCircle)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	Circle c1(Vector2(0, 0), 150);
	Circle c2(Vector2(0, 0), 20);

	EXPECT_TRUE(p.IsInside(c1));
	EXPECT_FALSE(p.IsInside(c2));
}

TEST(Polygon, IsInsidePolygon)
{
	Polygon a;
	a.SetPointCount(3);
	a.SetPoint(0, Vector2(-50, 0));
	a.SetPoint(1, Vector2(50, 0));
	a.SetPoint(2, Vector2(25, 50));
	a.ReCalc();

	Polygon b;
	b.SetPointCount(3);
	b.SetPoint(0, Vector2(-25, 5));
	b.SetPoint(1, Vector2(25, 5));
	b.SetPoint(2, Vector2(12.5, 25));
	b.ReCalc();

	EXPECT_FALSE(a.IsInside(b));
	EXPECT_TRUE(b.IsInside(a));
}

TEST(Polygon, OverlapsSegment)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	Segment s(Vector2(50, 0), Vector2(100, 0));

	EXPECT_TRUE(p.Overlaps(s));

	s.SetPoint(0, Vector2(51, 0));
	s.ReCalc();

	EXPECT_FALSE(p.Overlaps(s));
}

TEST(Polygon, OverlapsCircle)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(50, 0));
	p.SetPoint(1, Vector2(100, -50));
	p.SetPoint(2, Vector2(100, 50));
	p.ReCalc();

	Circle c(Vector2(0, 0), 50);

	EXPECT_TRUE(p.Overlaps(c));

	p.SetPoint(0, Vector2(51, 0));
	p.ReCalc();

	EXPECT_FALSE(p.Overlaps(c));
}

TEST(Polygon, OverlapsPolygon)
{
	Polygon a;
	a.SetPointCount(3);
	a.SetPoint(0, Vector2(-50, 0));
	a.SetPoint(1, Vector2(50, 0));
	a.SetPoint(2, Vector2(25, 50));
	a.ReCalc();

	Polygon b;
	b.SetPointCount(3);
	b.SetPoint(0, Vector2(-25, 5));
	b.SetPoint(1, Vector2(25, 5));
	b.SetPoint(2, Vector2(12.5, 25));
	b.ReCalc();

	EXPECT_TRUE(a.Overlaps(b));
	EXPECT_TRUE(b.Overlaps(a));

	Polygon c;
	c.SetPointCount(3);
	c.SetPoint(0, Vector2(51, 0));
	c.SetPoint(1, Vector2(101, 0));
	c.SetPoint(2, Vector2(25, 51));
	c.ReCalc();

	EXPECT_FALSE(c.Overlaps(a));
	EXPECT_FALSE(a.Overlaps(c));
}

TEST(Polygon, GetIntersectsSegment)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(25, 50));
	p.ReCalc();

	Segment s(Vector2(-51, 0), Vector2(51, 0));

	auto i = p.GetIntersects(s);

	ARE_EQ(i.size(), 2);

	ARE_EQ(50, i[0].x);
	ARE_EQ(0, i[0].y);

	ARE_EQ(-50, i[1].x);
	ARE_EQ(0, i[1].y);

	s = Segment(Vector2(-50, 0), Vector2(-50, 50));
	i = p.GetIntersects(s);

	ARE_EQ(i.size(), 1);
	ARE_EQ(-50, i[0].x);
	ARE_EQ(0, i[0].y);

	s = Segment(Vector2(-50, 51), Vector2(50, 51));
	i = p.GetIntersects(s);
	ARE_EQ(i.size(), 0);
}

TEST(Polygon, GetIntersectsCircle)
{
	Circle c1(Vector2(0, 0), 50);

	Polygon p1;
	p1.SetPointCount(3);
	p1.SetPoint(0, Vector2(-50, 0));
	p1.SetPoint(1, Vector2(50, 0));
	p1.SetPoint(2, Vector2(0, 50));
	p1.ReCalc();

	auto i = p1.GetIntersects(c1);

	ARE_EQ(i.size(), 3);

	ARE_EQ(50, i[0].x);
	ARE_EQ(0, i[0].y);

	ARE_EQ(-50, i[1].x);
	ARE_EQ(0, i[1].y);

	ARE_EQ(0, i[2].x);
	ARE_EQ(50, i[2].y);

	Circle c2(Vector2(0, 0), 150);
	i = p1.GetIntersects(c2);
	ARE_EQ(i.size(), 0);

	Polygon p2;
	p2.SetPointCount(3);
	p2.SetPoint(0, Vector2(101, 0));
	p2.SetPoint(1, Vector2(151, 0));
	p2.SetPoint(2, Vector2(126, 50));
	p2.ReCalc();

	i = p2.GetIntersects(c1);
	ARE_EQ(i.size(), 0);
}

TEST(Polygon, GetIntersectsPolygon)
{
	Polygon a;
	a.SetPointCount(3);
	a.SetPoint(0, Vector2(-50, 0));
	a.SetPoint(1, Vector2(50, 0));
	a.SetPoint(2, Vector2(0, 50));
	a.ReCalc();

	Polygon b;
	b.SetPointCount(3);
	b.SetPoint(0, Vector2(-50, 0));
	b.SetPoint(1, Vector2(50, 0));
	b.SetPoint(2, Vector2(25, 50));
	b.ReCalc();

	auto i = a.GetIntersects(b);

	ARE_EQ(3, i.size());

	ARE_EQ(50, i[0].x);
	ARE_EQ(0, i[0].y);

	ARE_EQ(-50, i[1].x);
	ARE_EQ(0, i[1].y);

	ARE_EQ(10, i[2].x);
	ARE_EQ(40, i[2].y);

	Polygon c;
	c.SetPointCount(3);
	c.SetPoint(0, Vector2(51, 0));
	c.SetPoint(1, Vector2(101, 0));
	c.SetPoint(2, Vector2(75, 50));
	c.ReCalc();

	i = a.GetIntersects(c);

	ARE_EQ(0, i.size());
}

TEST(Polygon, GetDisplacementSegment)
{
	Polygon p;
	p.SetPointCount(4);
	p.SetPoint(0, Vector2(-50, -50));
	p.SetPoint(1, Vector2(50, -50));
	p.SetPoint(2, Vector2(50, 50));
	p.SetPoint(3, Vector2(-50, 50));
	p.ReCalc();

	Segment s1(Vector2(0, 0), Vector2(0, 50));
	auto d = p.GetDisplacement(s1);
	ARE_EQ(51, d.Length());
	EXPECT_FALSE(p.Overlaps(mSegment(s1, d)));

	Segment s2(Vector2(25, 0), Vector2(25, 50));
	d = p.GetDisplacement(s2);
	ARE_EQ(26, d.Length());
	EXPECT_FALSE(p.Overlaps(mSegment(s2, d)));

	Segment s3(Vector2(51, 0), Vector2(51, 50));
	d = p.GetDisplacement(s3);
	ARE_EQ(0, d.Length());
}

TEST(Polygon, GetDisplacementCircle)
{
	Polygon p;
	p.SetPointCount(4);
	p.SetPoint(0, Vector2(-50, -50));
	p.SetPoint(1, Vector2(50, -50));
	p.SetPoint(2, Vector2(50, 50));
	p.SetPoint(3, Vector2(-50, 50));
	p.ReCalc();

	Circle c2(Vector2(0, 0), 50);
	auto d = p.GetDisplacement(c2);
	ARE_EQ(101, d.Length());
	EXPECT_FALSE(p.Overlaps(mCircle(c2, d)));

	Circle c3(Vector2(25, 0), 50);
	d = p.GetDisplacement(c3);
	ARE_EQ(76, d.Length());
	EXPECT_FALSE(p.Overlaps(mCircle(c3, d)));

	Circle c4(Vector2(101, 0), 50);
	d = p.GetDisplacement(c4);
	ARE_EQ(0, d.Length());
}

TEST(Polygon, GetDisplacementPolygon)
{
	Polygon a;
	a.SetPointCount(4);
	a.SetPoint(0, Vector2(-50, -50));
	a.SetPoint(1, Vector2(50, -50));
	a.SetPoint(2, Vector2(50, 50));
	a.SetPoint(3, Vector2(-50, 50));
	a.ReCalc();

	Polygon b;
	b.SetPointCount(4);
	b.SetPoint(0, Vector2(-25, -50));
	b.SetPoint(1, Vector2(75, -50));
	b.SetPoint(2, Vector2(75, 50));
	b.SetPoint(3, Vector2(-25, 50));
	b.ReCalc();

	auto d = a.GetDisplacement(b);
	ARE_EQ(76, d.Length());
	EXPECT_FALSE(a.Overlaps(mPolygon(b, d)));

	Polygon c;
	c.SetPointCount(4);
	c.SetPoint(0, Vector2(51, -50));
	c.SetPoint(1, Vector2(102, -50));
	c.SetPoint(2, Vector2(102, 50));
	c.SetPoint(3, Vector2(51, 50));
	c.ReCalc();

	d = c.GetDisplacement(a);
	ARE_EQ(0, d.Length());
}

// Collision is just above funcs rolled so just checking for consistency

TEST(Polygon, GetGollisionSegment)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(0, 50));
	p.ReCalc();

	Segment s(Vector2(-50, 0), Vector2(50, 0));

	Collision col = p.GetCollision(s);
	ARE_EQ(p.Overlaps(s), col.Overlaps());
	ARE_EQ(p.Contains(s), col.AcontainsB());
	ARE_EQ(s.Contains(p), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = p.GetIntersects(s);

	EXPECT_TRUE(vectorEQ(iC, iF));

	auto dC = col.GetDisplacement();
	auto dF = p.GetDisplacement(s);

	ARE_EQ(dC.x, dF.x);
	ARE_EQ(dC.y, dF.y);
}

TEST(Polygon, GetGollisionCircle)
{
	Polygon p;
	p.SetPointCount(3);
	p.SetPoint(0, Vector2(-50, 0));
	p.SetPoint(1, Vector2(50, 0));
	p.SetPoint(2, Vector2(0, 50));
	p.ReCalc();

	Circle c(Vector2(25, 25), 50);

	Collision col = p.GetCollision(c);
	ARE_EQ(p.Overlaps(c), col.Overlaps());
	ARE_EQ(p.Contains(c), col.AcontainsB());
	ARE_EQ(p.Contains(c), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = p.GetIntersects(c);

	EXPECT_TRUE(vectorEQ(iC, iF));

	auto dC = col.GetDisplacement();
	auto dF = p.GetDisplacement(c);

	ARE_EQ(dC.x, dF.x);
	ARE_EQ(dC.y, dF.y);
}

TEST(Polygon, GetGollisionPolygon)
{
	Polygon a;
	a.SetPointCount(4);
	a.SetPoint(0, Vector2(-50, -50));
	a.SetPoint(1, Vector2(50, -50));
	a.SetPoint(2, Vector2(50, 50));
	a.SetPoint(3, Vector2(-50, 50));
	a.ReCalc();

	Polygon b;
	b.SetPointCount(4);
	b.SetPoint(0, Vector2(-25, -50));
	b.SetPoint(1, Vector2(75, -50));
	b.SetPoint(2, Vector2(75, 50));
	b.SetPoint(3, Vector2(-25, 50));
	b.ReCalc();

	Collision col = a.GetCollision(b);
	ARE_EQ(a.Overlaps(b), col.Overlaps());
	ARE_EQ(a.Contains(b), col.AcontainsB());
	ARE_EQ(b.Contains(a), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = a.GetIntersects(b);

	ARE_EQ(iC.size(), iF.size());

	EXPECT_TRUE(vectorEQ(iC, iF));

	auto dC = col.GetDisplacement();
	auto dF = a.GetDisplacement(b);

	ARE_EQ(dC.x, dF.x);
	ARE_EQ(dC.y, dF.y);
}

// Double Disbatch test

TEST(Polygon, ContainsShape)
{
	ShapePtr aP(new Polygon());
	aP->SetPointCount(3);
	aP->SetPoint(0, Vector2(-50, 0));
	aP->SetPoint(1, Vector2(50, 0));
	aP->SetPoint(2, Vector2(25, 50));
	aP->ReCalc();

	ShapePtr bP(new Polygon());
	bP->SetPointCount(3);
	bP->SetPoint(0, Vector2(-25, 5));
	bP->SetPoint(1, Vector2(25, 5));
	bP->SetPoint(2, Vector2(12.5, 25));
	bP->ReCalc();

	Polygon aO = *dynamic_cast<Polygon*>(aP.get());
	Polygon bO = *dynamic_cast<Polygon*>(bP.get());

	EXPECT_EQ(aP->Contains(*bP), aO.Contains(bO));

	EXPECT_TRUE(aP->Contains(*bP));
	EXPECT_FALSE(bP->Contains(*aP));
}

TEST(Polygon, IsInsideShape)
{
	ShapePtr aP(new Polygon());
	aP->SetPointCount(3);
	aP->SetPoint(0, Vector2(-50, 0));
	aP->SetPoint(1, Vector2(50, 0));
	aP->SetPoint(2, Vector2(25, 50));
	aP->ReCalc();

	ShapePtr bP(new Polygon());
	bP->SetPointCount(3);
	bP->SetPoint(0, Vector2(-25, 5));
	bP->SetPoint(1, Vector2(25, 5));
	bP->SetPoint(2, Vector2(12.5, 25));
	bP->ReCalc();

	Polygon aO = *dynamic_cast<Polygon*>(aP.get());
	Polygon bO = *dynamic_cast<Polygon*>(bP.get());

	EXPECT_EQ(aP->IsInside(*bP), aO.IsInside(bO));

	EXPECT_FALSE(aP->IsInside(*bP));
	EXPECT_TRUE(bP->IsInside(*aP));
}

TEST(Polygon, OverlapsShape)
{
	ShapePtr aP(new Polygon());
	aP->SetPointCount(3);
	aP->SetPoint(0, Vector2(-50, 0));
	aP->SetPoint(1, Vector2(50, 0));
	aP->SetPoint(2, Vector2(25, 50));
	aP->ReCalc();

	ShapePtr bP(new Polygon());
	bP->SetPointCount(3);
	bP->SetPoint(0, Vector2(-25, 5));
	bP->SetPoint(1, Vector2(25, 5));
	bP->SetPoint(2, Vector2(12.5, 25));
	bP->ReCalc();

	ShapePtr cP(new Polygon());
	cP->SetPointCount(3);
	cP->SetPoint(0, Vector2(51, 0));
	cP->SetPoint(1, Vector2(101, 0));
	cP->SetPoint(2, Vector2(25, 51));
	cP->ReCalc();

	Polygon aO = *dynamic_cast<Polygon*>(aP.get());
	Polygon bO = *dynamic_cast<Polygon*>(bP.get());
	Polygon cO = *dynamic_cast<Polygon*>(cP.get());

	EXPECT_EQ(aP->Overlaps(*bP), aO.Overlaps(bO));
	EXPECT_EQ(aP->Overlaps(*cP), aO.Overlaps(cO));

	EXPECT_TRUE(aP->Overlaps(*bP));
	EXPECT_FALSE(bP->Overlaps(*cP));
}

TEST(Polygon, GetIntersectsShape)
{
	ShapePtr aP(new Polygon());
	aP->SetPointCount(3);
	aP->SetPoint(0, Vector2(-50, 0));
	aP->SetPoint(1, Vector2(50, 0));
	aP->SetPoint(2, Vector2(0, 50));
	aP->ReCalc();

	ShapePtr bP(new Polygon());
	bP->SetPointCount(3);
	bP->SetPoint(0, Vector2(-50, 0));
	bP->SetPoint(1, Vector2(50, 0));
	bP->SetPoint(2, Vector2(25, 50));
	bP->ReCalc();

	Polygon aO = *dynamic_cast<Polygon*>(aP.get());
	Polygon bO = *dynamic_cast<Polygon*>(bP.get());

	auto iP = aP->GetIntersects(*bP);
	auto iO = aO.GetIntersects(bO);

	EXPECT_TRUE(vectorEQ(iP, iO));
	EXPECT_EQ(iP.size(), 3);
}

TEST(Polygon, GetDisplacementShape)
{
	ShapePtr aP(new Polygon());
	aP->SetPointCount(4);
	aP->SetPoint(0, Vector2(-50, -50));
	aP->SetPoint(1, Vector2(50, -50));
	aP->SetPoint(2, Vector2(50, 50));
	aP->SetPoint(3, Vector2(-50, 50));
	aP->ReCalc();

	ShapePtr bP(new Polygon());
	bP->SetPointCount(4);
	bP->SetPoint(0, Vector2(-25, -50));
	bP->SetPoint(1, Vector2(75, -50));
	bP->SetPoint(2, Vector2(75, 50));
	bP->SetPoint(3, Vector2(-25, 50));
	bP->ReCalc();

	Polygon aO = *dynamic_cast<Polygon*>(aP.get());
	Polygon bO = *dynamic_cast<Polygon*>(bP.get());

	auto dP = aP->GetDisplacement(*bP);
	auto dO = aO.GetDisplacement(bO);

	EXPECT_EQ(dP, dO);

	ARE_EQ(76, dP.Length());
}

TEST(Polygon, GetGollisionShape)
{
	ShapePtr aP(new Polygon());
	aP->SetPointCount(4);
	aP->SetPoint(0, Vector2(-50, -50));
	aP->SetPoint(1, Vector2(50, -50));
	aP->SetPoint(2, Vector2(50, 50));
	aP->SetPoint(3, Vector2(-50, 50));
	aP->ReCalc();

	ShapePtr bP(new Polygon());
	bP->SetPointCount(4);
	bP->SetPoint(0, Vector2(-25, -50));
	bP->SetPoint(1, Vector2(75, -50));
	bP->SetPoint(2, Vector2(75, 50));
	bP->SetPoint(3, Vector2(-25, 50));
	bP->ReCalc();

	Polygon aO = *dynamic_cast<Polygon*>(aP.get());
	Polygon bO = *dynamic_cast<Polygon*>(bP.get());

	Collision colPtr = aP->GetCollision(*bP);
	Collision colObj = aO.GetCollision(bO);

	ARE_EQ(colPtr.Overlaps(), colObj.Overlaps());
	ARE_EQ(colPtr.AcontainsB(), colObj.AcontainsB());
	ARE_EQ(colPtr.BcontainsA(), colObj.BcontainsA());

	auto iP = colPtr.GetIntersects();
	auto iO = colObj.GetIntersects();

	EXPECT_TRUE(vectorEQ(iP, iO));

	ARE_EQ(colPtr.GetDisplacement().x, colObj.GetDisplacement().x);
	ARE_EQ(colPtr.GetDisplacement().y, colObj.GetDisplacement().y);
}
