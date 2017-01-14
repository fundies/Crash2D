#include "helper_func.hpp"


TEST(Circle, DefaultConstructor)
{
	Circle c;

	ARE_EQ(0, c.GetRadius());
	ARE_EQ(0, c.GetCenter().x);
	ARE_EQ(0, c.GetCenter().y);
}

TEST(Circle, ConstructorRadius)
{
	Circle c(Vector2(0, 0), 5);

	ARE_EQ(5, c.GetRadius());
	ARE_EQ(0, c.GetCenter().x);
	ARE_EQ(0, c.GetCenter().y);
}

// This does nothing
TEST(Circle, ReCalc)
{
	Circle c;
	c.ReCalc();

	ARE_EQ(0, c.GetRadius());
}

TEST(Circle, SetGetRadius)
{
	Circle c(Vector2(0, 0), 5);

	ARE_EQ(5, c.GetRadius());
	ARE_EQ(0, c.GetCenter().x);
	ARE_EQ(0, c.GetCenter().y);

	c.SetRadius(8);
	ARE_EQ(8, c.GetRadius());
}

TEST(Circle, Project)
{
	Circle c(Vector2(0, 0), 5);
	Projection p = c.Project(Axis(5, 5));

	ARE_EQ(-5, p.min);
	ARE_EQ(5, p.max);
}

TEST(Circle, ProjectShapeAxis)
{
	Circle c(Vector2(0, 0), 5);
	Projection p = c.Project(c, Axis(5, 5));

	ARE_EQ(-5, p.min);
	ARE_EQ(5, p.max);
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

TEST(Circle, IsInsideSegment)
{
	Circle c(Vector2(0, 0), 50);
	Segment s(Vector2(0, 0), Vector2(50, 0));

	EXPECT_FALSE(c.IsInside(s));
}

TEST(Circle, IsInsideCircle)
{
	Circle c1(Vector2(0, 0), 50);
	Circle c2(Vector2(10, 10), 25);

	EXPECT_FALSE(c1.IsInside(c2));
	EXPECT_TRUE(c2.IsInside(c1));
}

TEST(Circle, IsInsidePolygon)
{
	Circle c(Vector2(0, 0), 50);

	Polygon a;
	a.SetPointCount(3);
	a.SetPoint(0, Vector2(-10, 0));
	a.SetPoint(1, Vector2(0, 10));
	a.SetPoint(2, Vector2(10, 0));
	a.ReCalc();

	EXPECT_FALSE(c.IsInside(a));

	Polygon b;
	b.SetPointCount(4);
	b.SetPoint(0, Vector2(-50, -50));
	b.SetPoint(1, Vector2(50, -50));
	b.SetPoint(2, Vector2(50, 50));
	b.SetPoint(3, Vector2(-50, 50));
	b.ReCalc();

	EXPECT_TRUE(c.IsInside(b));
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

	ARE_EQ(i.size(), 2);

	ARE_EQ(50, i[0].x);
	ARE_EQ(0, i[0].y);

	ARE_EQ(-50, i[1].x);
	ARE_EQ(0, i[1].y);

	s = Segment(Vector2(-50, 50), Vector2(50, 50));
	i = c.GetIntersects(s);

	ARE_EQ(i.size(), 1);
	ARE_EQ(0, i[0].x);
	ARE_EQ(50, i[0].y);

	s = Segment(Vector2(-50, 51), Vector2(50, 51));
	i = c.GetIntersects(s);
	ARE_EQ(i.size(), 0);
}

TEST(Circle, GetIntersectsCircle)
{
	Circle c1(Vector2(0, 0), 50);
	Circle c2(Vector2(50, 0), 50);

	auto i = c1.GetIntersects(c2);

	ARE_EQ(i.size(), 2);

	ARE_EQ(25, i[0].x);
	ARE_EQ(-25 * std::sqrt(3), i[0].y);

	ARE_EQ(25, i[1].x);
	ARE_EQ(25 * std::sqrt(3), i[1].y);

	Circle c3(Vector2(100, 0), 50);

	i = c1.GetIntersects(c3);
	ARE_EQ(i.size(), 1);
	ARE_EQ(50, i[0].x);
	ARE_EQ(0, i[0].y);

	Circle c4(Vector2(101, 0), 50);

	i = c1.GetIntersects(c4);
	ARE_EQ(i.size(), 0);
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

	ARE_EQ(i.size(), 3);

	ARE_EQ(50, i[0].x);
	ARE_EQ(0, i[0].y);

	ARE_EQ(-50, i[1].x);
	ARE_EQ(0, i[1].y);

	ARE_EQ(0, i[2].x);
	ARE_EQ(50, i[2].y);

	Circle c2(Vector2(0, 0), 150);
	i = c2.GetIntersects(p1);
	ARE_EQ(i.size(), 0);

	Polygon p2;
	p2.SetPointCount(3);
	p2.SetPoint(0, Vector2(101, 0));
	p2.SetPoint(1, Vector2(151, 0));
	p2.SetPoint(2, Vector2(126, 50));
	p2.ReCalc();

	i = c1.GetIntersects(p2);
	ARE_EQ(i.size(), 0);
}

TEST(Circle, GetDisplacementSegment)
{
	Circle c(Vector2(0, 0), 50);

	Segment s1(Vector2(0, 0), Vector2(0, 50));
	auto d = c.GetDisplacement(s1);
	ARE_EQ(51, d.Length());
	EXPECT_FALSE(c.Overlaps(mSegment(s1, d)));

	Segment s2(Vector2(25, 0), Vector2(25, 50));
	d = c.GetDisplacement(s2);
	ARE_EQ(26, d.Length());
	EXPECT_FALSE(c.Overlaps(mSegment(s2, d)));

	Segment s3(Vector2(51, 0), Vector2(51, 50));
	d = c.GetDisplacement(s3);
	ARE_EQ(0, d.Length());
}

TEST(Circle, GetDisplacementCircle)
{
	Circle c1(Vector2(0, 0), 50);

	Circle c2(Vector2(0, 0), 50);
	auto d = c1.GetDisplacement(c2);
	ARE_EQ(101, d.Length());
	EXPECT_FALSE(c1.Overlaps(mCircle(c2, d)));

	Circle c3(Vector2(25, 0), 50);
	d = c1.GetDisplacement(c3);
	ARE_EQ(76, d.Length());
	EXPECT_FALSE(c1.Overlaps(mCircle(c3, d)));

	Circle c4(Vector2(101, 0), 50);
	d = c1.GetDisplacement(c4);
	ARE_EQ(0, d.Length());
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
	ARE_EQ(51, d.Length());
	EXPECT_FALSE(c.Overlaps(mPolygon(p1, d)));

	Polygon p2;
	p2.SetPointCount(3);
	p2.SetPoint(0, Vector2(-50, 25));
	p2.SetPoint(1, Vector2(50, 25));
	p2.SetPoint(2, Vector2(0, 75));
	p2.ReCalc();

	d = c.GetDisplacement(p2);
	ARE_EQ(26, d.Length());
	EXPECT_FALSE(c.Overlaps(mPolygon(p2, d)));

	Polygon p3;
	p3.SetPointCount(3);
	p3.SetPoint(0, Vector2(-50, 51));
	p3.SetPoint(1, Vector2(50, 51));
	p3.SetPoint(2, Vector2(0, 101));
	p3.ReCalc();

	d = c.GetDisplacement(p3);
	ARE_EQ(0, d.Length());
}

// Collision is just above funcs rolled so just checking for consistency

TEST(Circle, GetGollisionSegment)
{
	Circle c(Vector2(0, 0), 50);
	Segment s(Vector2(-50, 0), Vector2(50, 0));

	Collision col = c.GetCollision(s);
	ARE_EQ(c.Overlaps(s), col.Overlaps());
	ARE_EQ(c.Contains(s), col.AcontainsB());
	ARE_EQ(s.Contains(c), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = c.GetIntersects(s);

	ARE_EQ(iC.size(), iF.size());

	EXPECT_TRUE(vectorEQ(iF, iC));

	auto dC = col.GetDisplacement();
	auto dF = c.GetDisplacement(s);

	ARE_EQ(dC.x, dF.x);
	ARE_EQ(dC.y, dF.y);
}

TEST(Circle, GetGollisionCircle)
{
	Circle c1(Vector2(0, 0), 50);
	Circle c2(Vector2(25, 25), 50);

	Collision col = c1.GetCollision(c2);
	ARE_EQ(c1.Overlaps(c2), col.Overlaps());
	ARE_EQ(c1.Contains(c2), col.AcontainsB());
	ARE_EQ(c2.Contains(c1), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = c1.GetIntersects(c2);

	ARE_EQ(iC.size(), iF.size());

	EXPECT_TRUE(vectorEQ(iF, iC));

	auto dC = col.GetDisplacement();
	auto dF = c1.GetDisplacement(c2);

	ARE_EQ(dC.x, dF.x);
	ARE_EQ(dC.y, dF.y);
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
	ARE_EQ(c.Overlaps(p), col.Overlaps());
	ARE_EQ(c.Contains(p), col.AcontainsB());
	ARE_EQ(p.Contains(c), col.BcontainsA());

	auto iC = col.GetIntersects();
	auto iF = c.GetIntersects(p);

	ARE_EQ(iC.size(), iF.size());

	EXPECT_TRUE(vectorEQ(iF, iC));

	auto dC = col.GetDisplacement();
	auto dF = c.GetDisplacement(p);

	ARE_EQ(dC.x, dF.x);
	ARE_EQ(dC.y, dF.y);
}

// Double Disbatch tests

TEST(Circle, ContainsShape)
{
	ShapePtr aP(new Circle(Vector2(0, 0), 50));
	ShapePtr bP(new Circle(Vector2(20, 20), 20));

	Circle aO = *dynamic_cast<Circle*>(aP.get());
	Circle bO = *dynamic_cast<Circle*>(bP.get());

	EXPECT_EQ(aP->Contains(*bP), aO.Contains(bO));

	EXPECT_TRUE(aP->Contains(*bP));
	EXPECT_FALSE(bP->Contains(*aP));
}

TEST(Circle, IsInsideShape)
{
	ShapePtr aP(new Circle(Vector2(0, 0), 50));
	ShapePtr bP(new Circle(Vector2(0, 0), 20));

	Circle aO = *dynamic_cast<Circle*>(aP.get());
	Circle bO = *dynamic_cast<Circle*>(bP.get());

	EXPECT_EQ(aP->IsInside(*bP), aO.IsInside(bO));

	EXPECT_FALSE(aP->IsInside(*bP));
	EXPECT_TRUE(bP->IsInside(*aP));
}

TEST(Circle, OverlapsShape)
{
	ShapePtr aP(new Circle(Vector2(0, 0), 50));
	ShapePtr bP(new Circle(Vector2(20, 20), 20));

	Circle aO = *dynamic_cast<Circle*>(aP.get());
	Circle bO = *dynamic_cast<Circle*>(bP.get());

	EXPECT_EQ(aP->Overlaps(*bP), aO.Overlaps(bO));

	EXPECT_TRUE(aP->Overlaps(*bP));
}

TEST(Circle, GetIntersectsShape)
{
	ShapePtr aP(new Circle(Vector2(0, 0), 50));
	ShapePtr bP(new Circle(Vector2(50, 0), 50));

	Circle aO = *dynamic_cast<Circle*>(aP.get());
	Circle bO = *dynamic_cast<Circle*>(bP.get());

	auto iP = aP->GetIntersects(*bP);
	auto iO = aO.GetIntersects(bO);

	EXPECT_TRUE(vectorEQ(iP, iO));

	ARE_EQ(iP.size(), 2);

	EXPECT_TRUE(vectorContains(iP, Vector2(25, -25 * std::sqrt(3))));
	EXPECT_TRUE(vectorContains(iP, Vector2(25, 25 * std::sqrt(3))));
}

TEST(Circle, GetDisplacementShape)
{
	ShapePtr aP(new Circle(Vector2(0, 0), 50));
	ShapePtr bP(new Circle(Vector2(50, 0), 50));

	Circle aO = *dynamic_cast<Circle*>(aP.get());
	Circle bO = *dynamic_cast<Circle*>(bP.get());

	auto dP = aP->GetDisplacement(*bP);
	auto dO = aO.GetDisplacement(bO);

	EXPECT_EQ(dP, dO);

	ARE_EQ(51, dP.x);
	ARE_EQ(0, dP.y);
}

TEST(Circle, GetGollisionShape)
{
	ShapePtr aP(new Circle(Vector2(0, 0), 50));
	ShapePtr bP(new Circle(Vector2(25, 25), 50));

	Circle aO = *dynamic_cast<Circle*>(aP.get());
	Circle bO = *dynamic_cast<Circle*>(bP.get());

	Collision colPtr = aP->GetCollision(*bP);
	Collision colObj = aO.GetCollision(bO);

	ARE_EQ(colPtr.Overlaps(), colObj.Overlaps());
	ARE_EQ(colPtr.AcontainsB(), colObj.AcontainsB());
	ARE_EQ(colPtr.BcontainsA(), colObj.BcontainsA());

	auto iP = colPtr.GetIntersects();
	auto iO = colObj.GetIntersects();

	ARE_EQ(iP.size(), iO.size());

	EXPECT_TRUE(vectorEQ(iO, iP));

	ARE_EQ(colPtr.GetDisplacement().x, colObj.GetDisplacement().x);
	ARE_EQ(colPtr.GetDisplacement().y, colObj.GetDisplacement().y);
}
