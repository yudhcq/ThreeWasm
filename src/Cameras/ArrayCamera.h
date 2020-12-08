#pragma once
#include <vector>

#include "PerspectiveCamera.h"

namespace Three
{
    class ArrayCamera: public PerspectiveCamera
    {
    public:
        ArrayCamera();
    public:
        std::vector<PerspectiveCamera> cameras;
    };
} // namespace Three
