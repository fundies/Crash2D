#include "polygon.hpp"

#include <cmath>

const AxesVec& Polygon::GetAxes() const
{
	return _axes;
}

const unsigned Polygon::getPointCount() const
{
	return _points.size();
}

const Vector2 Polygon::getPoint(unsigned index) const
{
	return _points[index] + _pos;
}

void Polygon::generateAxes()
{
	_axes.clear();
	for (unsigned i = 0; i < getPointCount(); i++)
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
		_axes.push_back(normal);
	}
}

void Polygon::move(const Vector2 &offset)
{
	_pos += offset;
}

void Polygon::move(Precision_t x, Precision_t y)
{
	_pos += Vector2(x, y);
}

const Vector2 Polygon::getCenter() const
{
	Precision_t x = 0;
	Precision_t y = 0;
	for(unsigned i = 0; i < getPointCount(); i++)
	{
		x += _points[i].x;
		y += _points[i].y;
	}
	return Vector2(x / getPointCount(), y / getPointCount());
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
	Vector2 o = getCenter();

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
	a[0] = sf::Vertex(getPoint(0).asFloat(), _color);

	for(unsigned p = 0; p < getPointCount(); ++p)
		a[p + 1] = sf::Vertex(getPoint(p).asFloat(), _color);

	a[getPointCount()+1] = sf::Vertex(getPoint(0).asFloat(), _color);

	target.draw(a);
}

Projection Polygon::Project(Axis axis)
{
	Precision_t min = axis.dot(getPoint(0));
	Precision_t max = min;
	for (unsigned i = 1; i < getPointCount(); i++)
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

bool Polygon::triangleContains(Vector2 p, Vector2 a, Vector2 b, Vector2 c)
{
	// Compute vectors
	Vector2 v0 = c - a;
	Vector2 v1 = b - a;
	Vector2 v2 = p - a;

	// Compute dot products
	Precision_t dot00 = v0.dot(v0);
	Precision_t dot01 = v0.dot(v1);
	Precision_t dot02 = v0.dot(v2);
	Precision_t dot11 = v1.dot(v1);
	Precision_t dot12 = v1.dot(v2);

	// Compute barycentric coordinates
	Precision_t invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	Precision_t u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	Precision_t v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	// Check if point is in triangle
	return (u >= 0) && (v >= 0) && (u + v < 1);
}


bool Polygon::contains(Vector2 v)
{
	if (getPointCount() == 3)
		return triangleContains(v, getPoint(0), getPoint(1), getPoint(2));
	else
	{
		for (unsigned i = 0; i < getPointCount(); i++)
		{
			if (triangleContains(v, getCenter(), getPoint(i), getPoint(i + 1 == getPointCount() ? 0 : i + 1)))
				return true;
		}
	}

	return false;
}

bool Polygon::contains(Polygon p)
{
	for (unsigned v=0; v < p.getPointCount(); v++)
	{
		if (!contains(p.getPoint(v)))
			return false;
	}
	return true;
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

	bool contained = false;

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
			return Collision(translation, false, false);
		}
		else
		{
			// get the overlap
			Precision_t o = pA.getOverlap(pB);

			contained = (contains(p) || p.contains(*this));
			if (contained)
			{
				// get the overlap plus the distance from the minimum end points
				Precision_t mins = std::abs(pA.x - pB.x);
				Precision_t maxs = std::abs(pA.y - pB.y);

				if (mins < maxs)
					o += mins;
				else
					o += maxs;
			}

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
	translation = smallest * (Overlap+1);
	Vector2 distance = (p.getCenter()+ p.GetPos()) - (getCenter() + GetPos());
	
	if (translation.dot(distance) < 0)
		translation = -translation;

	return Collision(translation, true, contained);
}

Polygon& Polygon::SetPos(const Vector2& _pos) 
{
		this->_pos = _pos;
		return *this;
}

const Vector2& Polygon::GetPos() const
{
	return _pos;
}

Collision Polygon::GetCollision(Circle c)
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();// really large value;
	Axis smallest;
	
	Vector2 a = NearestVertex(c.GetPos());
	Vector2 b = getCenter() + GetPos();

	AxesVec axes = GetAxes();
	axes.push_back(a-b);

	bool contained = false;
	Vector2 translation;

	for (auto&& axis : axes)
	{
		
	Projection pA = Project(axis);
	Projection pB = c.Project(axis);
	
	if (!pA.overlaps(pB))
	{
		return Collision(translation, false, false);
	}
	else
	{
		Precision_t o = pA.getOverlap(pB);
		if (o < Overlap)
		{
			// then set this one as the smallest
			Overlap = o;
			smallest = axis;
		}
	}
	}

	return Collision(translation, true, contained);
}

Vector2 Polygon::NearestVertex(Vector2 point)
{
	Precision_t dist = std::numeric_limits<Precision_t>::infinity();
	Vector2 p;
	
	for (unsigned i=0; i < getPointCount(); i++)
	{
		Precision_t temp = GetDistance(point, getPoint(i));
		if (temp < dist)
		{
			dist = temp;
			p = getPoint(i);
		}
	}
	
	return p;
}

Precision_t Polygon::GetDistance(Vector2 a, Vector2 b)
{
	Vector2 v = a-b;
	return v.magnitude();
}