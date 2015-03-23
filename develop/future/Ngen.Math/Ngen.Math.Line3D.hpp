#ifndef _NGEN_MATH_LINE3D
#define _NGEN_MATH_LINE3D

#include "Ngen.Math.Vector3.hpp"

namespace Ngen {
	namespace Math {
	
		class Line3D {
		public:
			Vector3 A;
			Vector3 B;
			
			Line3D() : A(0), B(0) {}
		};
		
		typedef Line3D line3d;
		
	}
}