#ifndef _NGEN_MATH_COLORBOX2D
#define _NGEN_MATH_COLORBOX2D

#include "Ngen.Array.hpp"
#include "Ngen.Math.Color.hpp"

namespace Ngen {
	namespace Math {
	
		class ColorBox2D {
		public:
			
			ColorBox2D() : mWidth(0), mHeight(0), mXY(0) {}
			ColorBox2D(uwhole width, uwhole height, Color fill=Color(255)) : mWidth(width), mHeight(height), mXY(width*height) {
				for(int i = 0; i < mXY.Length(); ++i) {
					mXY[i] = fill;
				}
			}
			
			ColorBox2D(const ColorBox2D& copy, bool isReadOnly) : mWidth(copy.mWidth), mHeight(copy.mHeight),  mXY(copy.mXY, isReadOnly) {}
			
			ColorBox2D(const ColorBox2D& copy) : mWidth(copy.mWidth), mHeight(copy.mHeight),  mXY(copy.mXY, mXY.IsReadOnly()) {}
			
			ColorBox2D(ColorBox2D&& copy) : mWidth(copy.mWidth), mHeight(copy.mHeight),  mXY((Array<Color>&&)copy.mXY) {}
			
			Color& operator[](uwhole x, uwhole y) const {
				if(mXY.Length() == 0) {
					THROW(InvalidOperationException("The color box has not been initialized."));
				} else	if(x >= mWidth) {
					THROW(InvalidParameterException("The parameter 'x' cannot be greater-than or equal-to to width of the color box."));
				} else if(y >= mHeight) {
					THROW(InvalidParameterException("The parameter 'y' cannot be greater-than or equal-to to height of the color box."));
				}
				return mXY[x * y];
			}
			
		protected:
			real mWidth;
			real mHeight;
			Array<Color> mXY;
		};
		
		typedef ColorBox2D colorbox2d;
	}
}
#endif