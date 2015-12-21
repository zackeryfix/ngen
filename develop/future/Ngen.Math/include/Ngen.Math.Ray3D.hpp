#ifndef _NGEN_MATH_RAY3D
#define _NGEN_MATH_RAY3D

#include "Ngen.Math.Vector3.hpp"

namespace Ngen {
	namespace Math {
	
		class Ray3D {
		public:
			Vector3 Location;
			Vector3 Direction;
			
			Ray3D() : Location(0), Direction(0) {}
		};
		
		typedef Ray3D ray3d;
	}
}