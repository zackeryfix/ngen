
#ifndef _NGEN_MATH_VECTOR2
#define _NGEN_MATH_VECTOR2

#include "Ngen.Calculator.hpp"

namespace Ngen {
	namespace Math {
	
		class Vector2 {
		public:
			real X;
			real Y;
			
			Vector2() : X(0), Y(0) {}
			Vector2(real xy) : X(xy), Y(xy) {}
			Vector2(real x, real y) : X(x), Y(y) {}
			Vector2(const Vector2& copy) : X(copy.X), Y(copy.Y) {}
			
			real DistanceTo(const Vector2& b) const;
			Vector2 Rotated(const Vector2& center, real degrees) const;
			
		};
		
		typedef Vector2 vec2;
	}
}
#endif