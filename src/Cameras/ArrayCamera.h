#pragma once
#include <vector>

#include "PerspectiveCamera.h"

namespace Three
{
    class ArrayCamera: public PerspectiveCamera
    {
    public:
        ArrayCamera();
        std::vector<PerspectiveCamera>& Cameras();
    private:
        std::vector<PerspectiveCamera> mCameras;
    };
} // namespace Three
