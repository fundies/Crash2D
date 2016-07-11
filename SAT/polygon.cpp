#include "polygon.hpp"

#include <cmath>
#include <limits>

Polygon::Polygon()
{
	_color = sf::Color::White;
}

const AxesVec& Polygon::GetAxes() const
{
	return axes;
}

const unsigned Polygon::getPointCount() const
{
	return _points.size();
}

Vector2 Polygon::getPoint(unsigned index)
{
	return _points[index];
}

void Polygon::generateAxes()
{
	axes.clear();
	for (int i = 0; i < getPointCount(); i++)
	{
		// get the current vertex
		Vector2 p1 = getPoint(i);
		// get the next vertex
		Vector2 p2 =  getPoint(i + 1 == getPointCount() ? 0 : i + 1);
		// subtract the two to get the edge vector
		Vector2 edge = p1 - p2;
		// get either perpendicular vector
		Axis normal = edge.perpendicular().normalize();
		// the perp method is just (x, y) => (-y, x) or (y, -x)
		axes.push_back(normal);
	}
}

void Polygon::move(const Vector2 &offset)
{
	for (auto&& p : _points)
		p += offset;

	generateAxes();
}

void Polygon::move(Precision_t x, Precision_t y)
{
	for (auto&& p : _points)
		p += Vector2(x, y);

	generateAxes();
}

const Vector2 Polygon::getOrigin() const
{
	Precision_t x = 0;
	Precision_t y = 0;
	for(int i = 0; i < getPointCount(); i++)
	{
		x += _points[i].x;
		y += _points[i].y;
	}
	return Vector2(x / getPointCount(), y / getPointCount());
}

void Polygon::setFillColor(sf::Color c)
{
	_color = c;
}

void Polygon::setPointCount(unsigned c)
{
	_points.resize(c);
}

void Polygon::setPoint(unsigned i, Vector2 p)
{
	_points[i] = p;
}

void Polygon::rotate(Precision_t angle)
{
	Precision_t radians = (angle * M_PI ) / 180;
	Vector2 o = getOrigin();

	for (auto&& p : _points)
	{
		p -= o;

		Precision_t x = p.y * std::sin(radians) + p.x * std::cos(radians);
		Precision_t y = p.y * std::cos(radians) - p.x * std::sin(radians);

		p.x = x;
		p.y = y;

		p += o;
	}

	generateAxes();
}


void Polygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray a(sf::TrianglesFan, _points.size() + 2);
	a[0] = (sf::Vertex(sf::Vector2f(getOrigin().x, getOrigin().y), _color));

	for(unsigned p = 0; p < _points.size(); ++p)
	{
		Vector2 k = _points[p];
		a[p + 1] = (sf::Vertex(sf::Vector2f(k.x, k.y), _color));
	}

	a[getPointCount()+1] = (sf::Vertex(sf::Vector2f(_points[0].x, _points[0].y), _color));

	target.draw(a);
}

Projection Polygon::Project(Axis axis)
{
	Precision_t min = axis.dot(getPoint(0));
	Precision_t max = min;
	for (int i = 1; i < getPointCount(); i++)
	{
		Precision_t prj = axis.dot(getPoint(i));
		if (prj < min)
		{
			min = prj;
		}
		else if (prj > max)
		{
			max = prj;
		}
	}
	return Projection(min, max);
}

Collision Polygon::GetCollision(Polygon p)
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();// really large value;

	Axis smallest;
	Vector2 translation;
	AxesVec axes;

	const AxesVec A = GetAxes();
	const AxesVec B = p.GetAxes();

	// Combine Vectors A&B
	axes.reserve(A.size() + B.size()); // preallocate memory
	axes.insert(axes.end(), A.begin(), A.end());
	axes.insert(axes.end(), B.begin(), B.end());

	// loop over the axes
	for (auto&& axis : axes)
	{
		// project both shapes onto the axis
		Projection pA = Project(axis);
		Projection pB = p.Project(axis);
		// do the projections overlap?
		if (!pA.overlaps(pB))
		{
			// then we can guarantee that the shapes do not overlap
			return Collision(translation, false);
		}
		else
		{
			// get the overlap
			Precision_t o = pA.getOverlap(pB);
			// check for minimum
			if (o < Overlap)
			{
				// then set this one as the smallest
				Overlap = o;
				smallest = axis;
			}
		}
	}

	// if we get here then we know that every axis had overlap on it
	// so we can guarantee an intersection

	// gurantee the translation is away from other shape
	translation = smallest * (std::abs(Overlap)+1);
	Vector2 distance = (getOrigin()) - (p.getOrigin());
	if (translation.dot(distance) > 0)
		translation = -translation;

	return Collision(translation, true);
}
