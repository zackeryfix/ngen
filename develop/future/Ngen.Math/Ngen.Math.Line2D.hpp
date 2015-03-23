#ifndef _NGEN_MATH_LINE2D
#define _NGEN_MATH_LINE2D

#include "Ngen.Math.Vector2.hpp"

namespace Ngen {
	namespace Math {
	
		class Line2D {
		public:
			Vector2 A;
			Vector2 B;
			
			Line2D() : PointA(0), PointB(0) {}
		};
		
		typedef Line2D line2d;
	}
}
#endif