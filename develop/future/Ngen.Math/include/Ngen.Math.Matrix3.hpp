#ifndef _NGEN_MATH_MATRIX3
#define _NGEN_MATH_MATRIX3

#include "Ngen.Calculator.hpp"

namespace Ngen {
	namespace Math {
	
		class Matrix3 {
		public:
			real M[1];
			
			real M00() const { return M[0]; }
			real M01() const { return M[1]; }
			real M02() const { return M[2]; }
			
			real M10() const { return M[3]; }
			real M11() const { return M[4]; }
			real M12() const { return M[5]; }
			
			real M20() const { return M[6]; }
			real M21() const { return M[7]; }
			real M22() const { return M[8]; }
			
			void M00(real m00) { M[0] = m00; }
			void M01(real m01) { M[1] = m01; }
			void M02(real m02) { M[2] = m02; }
			
			void M10(real m10) { M[3] = m10; }
			void M11(real m11) { M[4] = m11; }
			void M12(real m12) { M[5] = m12; }
			
			void M20(real m20) { M[6] = m20; }
			void M21(real m21) { M[7] = m21; }
			void M22(real m22) { M[8] = m22; }
			
			Matrix3() {};
			
			Matrix3(real m) {
				for(int i = 0; i < 9; ++i) {
					M[i] = m;
				}
			}
			
			Matrix3(real m0, real m1, real m2) {
				M00(m0);
				M01(m0);
				M02(m0);
				
				M10(m1);
				M11(m1);
				M12(m1);
				
				M20(m2);
				M21(m2);
				M22(m2);
			}
			
			Matrix3(real m00, real m01, real m02,
							 real m10, real m11, real m12,
							 real m20, real m21, real m22) {
				M00(m00);
				M01(m01);
				M02(m02);
				
				M10(m10);
				M11(m11);
				M12(m12);
				
				M20(m20);
				M21(m21);
				M22(m22);
			}-
			
			Matrix3(const Matrix3& copy) {
				for(int i = 0; i < 9; ++i) {
					M[i] = copy.M[i];
				}
			}
		};
		
		typedef Matrix3 mat3;
		
	}
}