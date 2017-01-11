#include "helper_func.hpp"

Segment mSegment(Segment s, Vector2 displacement)
{
	return Segment(s.GetPoint(0) + displacement, s.GetPoint(1) + displacement);
}

Circle mCircle(Circle c, Vector2 displacement)
{
	return Circle(c.GetCenter() + displacement, c.GetRadius());

}

Polygon mPolygon(Polygon p, Vector2 displacement)
{
	Polygon pD;

	pD.SetPointCount(p.GetPointCount());

	for (unsigned i = 0; i < p.GetPointCount(); ++i)
	{
		pD.SetPoint(i, p.GetPoint(i) + displacement);
	}

	pD.ReCalc();

	return pD;
}
