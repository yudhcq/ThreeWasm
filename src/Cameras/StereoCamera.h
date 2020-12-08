#pragma once
#include "Camera.h"
#include "PerspectiveCamera.h"

namespace Three
{
    class StereoCamera : public Camera
    {
    public:
        StereoCamera();
        void Update(const PerspectiveCamera& camera);
    public:
        double aspect;
        double eysSep;
        PerspectiveCamera cameraL;
        PerspectiveCamera cameraR;
    };
} // namespace Three
