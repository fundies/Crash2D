#ifndef HELPER_FUNC_HPP
#define HELPER_FUNC_HPP

#include "circle.hpp"
#include "polygon.hpp"
#include "segment.hpp"
#include "projection.hpp"
#include "collision.hpp"
#include "transform.hpp"

#include <gtest/gtest.h>
#include <memory>

using ShapePtr = std::unique_ptr<Shape>;
const double ULP = 0.0001;

#define ARE_EQ(a, b) EXPECT_NEAR(a, b, ULP);

Segment mSegment(Segment s, Vector2 displacement);
Circle mCircle(Circle c, Vector2 displacement);
Polygon mPolygon(Polygon p, Vector2 displacement);

bool vectorContains(std::vector<Vector2> &coords, Vector2 pt);
bool vectorEQ(std::vector<Vector2> &a, std::vector<Vector2> &b);

#endif
