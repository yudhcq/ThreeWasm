#pragma once
#include "../Core//Object3D.h"

namespace Three
{
    class WebGLCubeRenderTarget;
    class WebGLRenderer;
    class Scene;
    class CubeCamera: public Object3D
    {
    public:
        CubeCamera(double near, double far, std::shared_ptr<WebGLCubeRenderTarget> renderTarget);
        void Update(const WebGLRenderer& renderer, const Scene& scene);
        void Clear(const WebGLRenderer& renderer, bool color, bool depth, bool stencil);
    public:
        std::shared_ptr<WebGLCubeRenderTarget> renderTarget;
    };
} // namespace Three
