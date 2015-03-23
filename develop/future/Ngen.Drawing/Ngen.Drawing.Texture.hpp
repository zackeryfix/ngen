
#ifndef _NGEN_DRAWING_TEXTURE
#define _NGEN_DRAWING_TEXTURE

namespace Ngen {
	namespace Drawing {
		
		class Texture : public RenderTarget {
		public:
			
			Texture() : RenderTarget() {}
			Texture(uwhole width, uwhole height) : RenderTarget(width, height) {
				mResourceId = glLoadTexture(0, mWidth*mHeight, GL_PIXELFORMAT_RGBA4444);
			}
			Texture(const ColorBox2D* image) : RenderTarget(image.Width, image.Height) {
				mResourceId = glLoadTexture( (byte*)&image[0] , mWidth*mHeight, GL_PIXELFORMAT_RGBA4444);
				mIsLoaded = (mResourceId > 0);
			}
			
			
		};
	}
}
#endif