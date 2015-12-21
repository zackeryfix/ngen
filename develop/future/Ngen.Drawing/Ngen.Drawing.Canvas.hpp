#ifndef __NGEN_DRAWING_CANVAS_HPP
#define __NGEN_DRAWING_CANVAS_HPP



namespace Ngen {
   namespace Drawing {
      ngen_api class CanvasCreationParams {
      public:
         word Width;
         word Height;
         word ColorDepth;
         word StencilDepth;
         word ZBufferDepth;
         word FieldOfView;
         word AspectRatio;
         word FramePerSecond;
         bool IsFullscreen;
         bool IsResizable;
         bool MaintainAspectRatio;
      };

      ngen_api class Canvas : public RenderTarget {


      };
   }
}
#endif // __NGEN_DRAWING_CANVAS_HPP
