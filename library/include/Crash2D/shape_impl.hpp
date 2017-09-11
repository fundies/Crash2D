#ifndef CRASH2D_SHAPE_IMPL_HPP
#define CRASH2D_SHAPE_IMPL_HPP

#include <Crash2D/shape.hpp>

namespace Crash2D
{
class ShapeImpl : virtual public Shape
{
public:
	//! Constructs a default shape.
	/*!
		This shape's points must be added manually.
	*/
	ShapeImpl();

	//! Constructs a default shape with center coordinate.
	/*!
		\param c The center point of the shape.
		This shape's points must be added manually.
	*/
	ShapeImpl(const Vector2 c);

	//! Gets the center of this shape.
	/*!
		\return The center of this shape.
	*/
	virtual const Vector2& GetCenter() const override;

	//! Sets the number of points in this shape.
	/*!
		\param c The number of points in this shape.
	*/
	virtual void SetPointCount(const unsigned &c) override;

	//! Sets the point of this shape at the given index to the new point.
	/*!
		\param i The index of the point.
		\param p The new point to replace the old point with.
	*/
	virtual void SetPoint(const unsigned &i, const Vector2 &p) override;

	//! Gets the number of points in this shape.
	/*!
		\return The number of points in this shape.
	*/
	virtual const unsigned GetPointCount() const override;

	//! Gets the point of this shape at the given index.
	/*!
		\param i The index of the point.
		\return The point of this shape at the given index.
	*/
	virtual const Vector2& GetPoint(const unsigned &i) const override;

	//! Gets the points this shape is composed of.
	/*!
		\return The points this shape is composed of.
	*/
	virtual const std::vector<Vector2>& GetPoints() const override;

	//! Method used to caculate the overlap of two shapes
	/*!
		\param axes Axes used in calculations.
		\param a Shape a;
		\param b Shape b;
	*/
	virtual const Precision_t GetOverlap(const AxesVec &axes, const Shape &a, const Shape &b) const override;
	
	//! Method used to caculate displacment of two shapes
	/*!
		\param axes Axes used in calculations.
		\param a Shape a;
		\param b Shape b;
	*/
	virtual const Vector2 CalcDisplacement(const AxesVec &axes, const Shape &a, const Shape &b) const;
	

	//! Applies a transformation to this shape..
	/*!
		\param t The transformation to be applied.
	*/
	virtual void Transform(const Transformation &t) override;

	//! Method required to be called after updating the geometry of a shape.
	/*!
	*/
	virtual void ReCalc() override;

protected:

	std::vector<Vector2> _points; /*!< The points this shape is composed of. */
	Vector2 _center; /*!< The center of this shape. */
};
}

#endif
