
#ifndef _NGEN_MATH_VECTOR4
#define _NGEN_MATH_VECTOR4

#include "Ngen.Calculator.hpp"

namespace Ngen {
	namespace Math {
	
		class Vector4 {
		public:
			real X;
			real Y;
			real Z;
			real W;
			
			Vector4() : X(0), Y(0), Z(0), W(0) {}
			Vector4(real xyzw) : X(xyzw), Y(xyzw), Z(xyzw), W(xyzw) {}
			Vector4(real x, real y, real z, real w) : X(x), Y(y), Z(z), W(w) {}
			Vector4(const Vector4& copy) : X(copy.X), Y(copy.Y), Z(copy.Z), W(copy.W) {}
		};
		
		typedef Vector4 vec4;
	}
}
#endif