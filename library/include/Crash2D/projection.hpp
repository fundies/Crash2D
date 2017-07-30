#ifndef CRASH2D_PROJECTION_HPP
#define CRASH2D_PROJECTION_HPP

#include <Crash2D/vector2.hpp>

namespace Crash2D
{
//!  A class representing a two-dimensional projection. */
class Projection// : public Vector2
{
public:
	//! Constructs a default projection.
	/*!
	*/
	Projection();

	//! Constructs a projection from a min and max
	/*!
		\param min projection mininmum
		\param max projection maximum
	*/
	Projection(const Precision_t min, const Precision_t max);

	//! Checks for overlap between this projection and the given projection.
	/*!
		\param p A given projection to test for overlap against this.
	*/
	const bool IsOverlap(const Projection &p) const;

	//! Gets the overlap between this projection and the given projection.
	/*!
		\param p The projection used in calculating the overlap.
	*/
	const Precision_t GetOverlap(const Projection &p) const;

	Precision_t min; /*!< The projection minimum */
	Precision_t max; /*!< The projection maximum */

};
}

#endif
