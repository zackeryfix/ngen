#ifndef _NGEN_MATH_SPHERE3D
#define _NGEN_MATH_SPHERE3D

#include "Ngen.Math.Vector3.hpp"

namespace Ngen {
	namespace Math {
	
		class Sphere3D {
		public:
			Vector3 Location;
			real Radius;
			
			Sphere3D() : Location(0), Radius(0) {}
		};
		
		
		typedef Sphere3D sphere3d;
	}
}