#pragma once
#include "Camera.h"

namespace Three
{
    struct View;
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera
        (
            double fov = 50.,
            double aspect = 1.,
            double near = 0.1,
            double far = 2000.
        );
        void SetFocalLength(double focalLength);
        double GetFocalLength() const;
        double GetEffectiveFOV() const;
        double GetFilmWidth() const;
        double GetFilmHeight() const;

        void UpdateProjectionMatrix();
        void SetViewOffset(double fullWidth, double fullHeight, double offsetX, double offsetY, double width, double height);
        void ClearViewOffset();
        virtual std::string ToJson() const;
    public:
        double zoom;
        double fov;
        double aspect;
        double near;
        double far;
        double focus;
        std::shared_ptr<View> view;
        double filmGauge;
        double filmOffset;
    };
} // namespace Three
