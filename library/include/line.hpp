#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"

class Line : public Shape
{
public:
	Line();
	Line(const Vector2 &a, const Vector2 &b);

	void SetPoint(const unsigned &i, const Vector2 &p);

	const Precision_t DistancePoint(const Vector2 &p) const;
	const Precision_t SignedDistancePoint(const Vector2 &p) const;
	const Precision_t& GetLength() const;
	const Precision_t& GetSlope() const;

	const bool IsPerpendicular(const Line &l) const;
	const bool IsParallel(const Line &l) const;

	const bool ContainsPoint(const Vector2 &) const;

	const bool Intersects(const Line &l) const;
	const Vector2 GetIntersect(const Line &l) const;

	const Vector2 GetTranslation(const Line &l) const;

	void Rotate(const Precision_t &a);

	const Axis& GetAxis() const;

private:

	void Recalc();

	Precision_t _slope;
	Precision_t _length;

	Axis _axis;
};

#endif // LINE_HPP
