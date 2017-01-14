#include "helper_func.hpp"

#include <gtest/gtest.h>

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

bool vectorContains(std::vector<Vector2> &coords, Vector2 pt)
{
	auto it = std::find(std::begin(coords), std::end(coords), pt);
	return (it != std::end(coords));
}

bool vectorEQ(std::vector<Vector2> &a, std::vector<Vector2> &b)
{
	if (a.size() != b.size())
		return false;

	for (auto i : a)
	{
		if (!vectorContains(b, i))
			return false;
	}

	return true;
}
