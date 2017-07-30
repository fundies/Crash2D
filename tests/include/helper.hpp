#ifndef HELPER_HPP
#define HELPER_HPP

#include <Crash2D/circle.hpp>
#include <Crash2D/polygon.hpp>
#include <Crash2D/segment.hpp>
#include <Crash2D/projection.hpp>
#include <Crash2D/collision.hpp>
#include <Crash2D/transformation.hpp>

#include <gtest/gtest.h>
#include <memory>
#include <cmath>

using namespace Crash2D;

using ShapePtr = std::unique_ptr<Shape>;
const double ULP = 0.0001;

#define ARE_EQ(a, b) EXPECT_NEAR(a, b, ULP);

Segment mSegment(Segment s, Vector2 displacement);
Circle mCircle(Circle c, Vector2 displacement);
Polygon mPolygon(Polygon p, Vector2 displacement);

bool vectorContains(std::vector<Vector2> &coords, Vector2 pt);
bool vectorEQ(std::vector<Vector2> &a, std::vector<Vector2> &b);

#endif
