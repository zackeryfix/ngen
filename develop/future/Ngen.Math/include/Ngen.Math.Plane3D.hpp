#ifndef _NGEN_MATH_PLANE3D
#define _NGEN_MATH_PLANE3D

#include "Ngen.Math.Vector3.hpp"

namespace Ngen {
	namespace Math {
	
		class Plane3D {
		public:
			Vector3 Location;
			real D;
			
			Plane3D() : Location(0), D(0) {}
		};
		
		typedef Plane3D plane3d;
		
	}
}