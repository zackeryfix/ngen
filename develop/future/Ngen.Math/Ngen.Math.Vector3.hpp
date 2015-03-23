
#ifndef _NGEN_MATH_VECTOR3
#define _NGEN_MATH_VECTOR3

#include "Ngen.Calculator.hpp"

namespace Ngen {
	namespace Math {
	
		class Vector3 {
		public:
			real X;
			real Y;
			real Z;
			
			Vector3() : X(0), Y(0), Z(0) {}
			Vector3(real xyz) : X(xyz), Y(xyz), Z(xyz) {}
			Vector3(real x, real y, real z) : X(x), Y(y), Z(z) {}
			Vector3(const Vector3& copy) : X(copy.X), Y(copy.Y), Z(copy.Z) {}
			
			real Magnitude() const:
			real MagnitudeSq() const;
			real DistanceTo(const Vector3& b) const;
			real DistanceToSq(const Vector3& b) const;
			real Dot(const Vector3& rhs) const;
			Vector3 Cross(const Vector3& rhs) const;
		};
		
		typedef Vector3 vec3;
	}
}
#endif