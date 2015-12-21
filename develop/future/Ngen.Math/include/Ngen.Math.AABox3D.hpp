#ifndef _NGEN_MATH_AABOX3D
#define _NGEN_MATH_AABOX3D

#include "Ngen.Math.Vector3.hpp"

namespace Ngen {
	namespace Math {
	
		class AxisAlignedBox3D {
		public:
			Vector3 Min;
			Vector3 Max;
			
			 AxisAlignedBox3D () : Min(0), Max(0) {}
		};
		
		
		typedef AxisAlignedBox3D aabox3d;
	}
}