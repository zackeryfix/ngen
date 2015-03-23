
#ifndef _NGEN_MATH_COLOR
#define _NGEN_MATH_COLOR

#include "Ngen.Calculator.hpp"

namespace Ngen {
	namespace Math {
	
		class Color {
		public:
			real R;
			real G;
			real B;
			real A;
			
			Color() : R(0), G(0), B(0), A(0) {}
			Color(real rgba) : R(rgba), G(rgba), B(rgba), A(rgba) {}
			Color(real r, real g, real b, real a) : R(r), G(g), B(b), A(a) {}
			Color(const Color& copy) : R(copy.R), G(copy.G), B(copy.B), A(copy.A) {}
		};
	}
}