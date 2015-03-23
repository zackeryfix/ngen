
#ifndef _NGEN_GRAPHICS_RENDERTARGET
#define _NGEN_GRAPHICS_RENDERTARGET

namespace Ngen {
	namespace Graphics {
		
		class RenderTarget {
		public:
			
			RenderTarget() mGLId(0), mWidth(0), mHeight(0) {}
			RenderTarget(uwhole width, uwhole height) : mGLId(0), mWidth(width), mHeight(height) {}
			
		protected:
			uwhole mGLId;
			uwhole mWidth;
			uwhole mHeight;
			
		};
	}
}
#endif