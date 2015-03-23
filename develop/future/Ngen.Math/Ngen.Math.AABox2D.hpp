#ifndef _NGEN_MATH_AABOX2D
#define _NGEN_MATH_AABOX2D

#include "Ngen.Math.Vector2.hpp"

namespace Ngen {
	namespace Math {
	
		class AxisAlignedBox2D {
		public:
			Vector2 Min;
			Vector2 Max;
			
			 AxisAlignedBox2D () : Min(0), Max(0) {}
		};
		
		
		typedef AxisAlignedBox2D aabox2d;
	}
}