#include <iostream>
#include <math.h>
#include <limits>
#include <SFML/Graphics.hpp>

using Precision_t = float;

class Vector2 : public sf::Vector2<Precision_t>
{
public:
	Vector2() : sf::Vector2<Precision_t>(0 ,0) {}
	Vector2(Precision_t x, Precision_t y) : sf::Vector2<Precision_t>(x,y) {}
	Vector2(const sf::Vector2<Precision_t> &v)
	{
		x = v.x;
		y = v.y;
	}

	Vector2 perpendicular();
	Precision_t dot(Vector2 v);
	Precision_t magnitude();
	Vector2 normalize();

};

Vector2 Vector2::perpendicular()
{
	return Vector2(y, -x);
}

Precision_t Vector2::dot(Vector2 v)
{
	return (x * v.x) + (y * v.y);
}

Precision_t Vector2::magnitude()
{
	return std::sqrt(dot(*this));
}

Vector2 Vector2::normalize()
{
	return *this / magnitude();
}


class Projection : public sf::Vector2<Precision_t>
{
public:
	Projection() : sf::Vector2<Precision_t>(0 ,0) {}
	Projection(Precision_t min, Precision_t max) : sf::Vector2<Precision_t>(min, max) {}
	Projection(const sf::Vector2<Precision_t> &v)
	{
		x = v.x;
		y = v.y;
	}

	bool overlaps(Projection p);
	Precision_t getOverlap(Projection p);
};

bool Projection::overlaps(Projection p)
{
	// x = min & y = max
	return !(x > p.y || p.x > y);
}

Precision_t Projection::getOverlap(Projection p)
{
	// x = min & y = max
	return std::min(y, p.y) - std::max(x, p.x);
}

using Axis = Vector2;
using AxesVec = std::vector<Axis>;

class Collision
{
private:
	bool _touching;
	Vector2 _translation;

public:

	Collision(Vector2 translation, bool touching)
	{
		_touching = touching;
		_translation = translation;
	}

	bool IsTouching() const
	{
		return _touching;
	}

	const Vector2& GetTranslation() const
	{
		return _translation;
	}
};

class Polygon : public sf::Drawable
{
private:
	AxesVec axes;
	std::vector<Vector2> _points;
	sf::Color _color;

public:
	Polygon()
	{
		_color = sf::Color::White;
	}

	const AxesVec& GetAxes() const
	{
		return axes;
	}

	const unsigned getPointCount() const
	{
		return _points.size();
	}

	Vector2 getPoint(unsigned index)
	{
		return _points[index];
	}

	void generateAxes()
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

	void move(const Vector2 &offset)
	{
		for (auto&& p : _points)
			p += offset;

		generateAxes();
	}

	void move(Precision_t x, Precision_t y)
	{
		for (auto&& p : _points)
			p += Vector2(x, y);

		generateAxes();
	}

	const Vector2 getOrigin() const
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

	void setFillColor(sf::Color c)
	{
		_color = c;
	}

	void setPointCount(unsigned c)
	{
		_points.resize(c);
	}

	void setPoint(unsigned i, Vector2 p)
	{
		_points[i] = p;
	}

	void rotate(Precision_t angle)
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

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
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
};

Vector2 Project(Polygon p, Axis axis)
{
	Precision_t min = axis.dot(p.getPoint(0));
	Precision_t max = min;
	for (int i = 1; i < p.getPointCount(); i++)
	{
		Precision_t prj = axis.dot(p.getPoint(i));
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

Collision GetCollision(Polygon a, Polygon b)
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();// really large value;

	Axis smallest;
	Vector2 translation;
	AxesVec axes;

	const AxesVec A = a.GetAxes();
	const AxesVec B = b.GetAxes();

	// Combine Vectors A&B
	axes.reserve(A.size() + B.size()); // preallocate memory
	axes.insert(axes.end(), A.begin(), A.end());
	axes.insert(axes.end(), B.begin(), B.end());

	// loop over the axes
	for (auto&& axis : axes)
	{
		// project both shapes onto the axis
		Projection pA = Project(a, axis);
		Projection pB = Project(b, axis);
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
	Vector2 distance = (a.getOrigin()) - (b.getOrigin());
	if (translation.dot(distance) > 0)
		translation = -translation;

	return Collision(translation, true);
}

int main(int argc, char **argv)
{
	Polygon polygon;
	polygon.setFillColor(sf::Color::Red);
	polygon.setPointCount(3);
	polygon.setPoint(0, Vector2(500, 100));
	polygon.setPoint(1, Vector2(250, 500));
	polygon.setPoint(2, Vector2(750, 500));
	polygon.generateAxes();

	Polygon polygon2;
	polygon2.setFillColor(sf::Color::Green);
	polygon2.setPointCount(3);
	polygon2.setPoint(0, Vector2(200, 0));
	polygon2.setPoint(1, Vector2(400, 150));
	polygon2.setPoint(2, Vector2(250, 150));
	polygon2.generateAxes();

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		int hdir = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		int vdir = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		int rdir = sf::Keyboard::isKeyPressed(sf::Keyboard::Z) - sf::Keyboard::isKeyPressed(sf::Keyboard::X);

		polygon2.rotate(rdir);

		polygon2.move(hdir*4, vdir*4);

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(polygon);
		window.draw(polygon2);

		Collision c = GetCollision(polygon, polygon2);

		if (c.IsTouching())
		{
			polygon2.move(c.GetTranslation());
			polygon2.setFillColor(sf::Color::Blue);
		}
		else
		{
			polygon2.setFillColor(sf::Color::Green);
		}

		window.display();
	}

	return 0;
}
