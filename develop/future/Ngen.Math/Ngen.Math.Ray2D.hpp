#ifndef _NGEN_MATH_RAY2D
#define _NGEN_MATH_RAY2D

#include "Ngen.Math.Vector2.hpp"

namespace Ngen {
	namespace Math {
	
		class Ray2D {
		public:
			Vector2 Location;
			Vector2 Direction;
			
			Ray2D() : Location(0), Direction(0) {}
		};
		
		
		typedef Ray2D ray2d;
	}
}