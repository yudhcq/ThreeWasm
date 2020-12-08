#pragma once
#include "Camera.h"

namespace Three
{
    class Matrix4;
    class Vector3;

    struct View
    {
        bool enable = true;
        double fullWidth = 1.;
        double fullHeight = 1.;
        double offsetX = 0.;
        double offsetY = 0.;
        double width = 1.;
        double height = 1.;
    };

    class OrthographicCamera: public Camera
    {
    public:
        OrthographicCamera
        (
            double left = -1.,
            double right = 1., 
            double top = 1., 
            double bottom = -1., 
            double near = 0.1, 
            double far = 2000.
        );
        void UpdateProjectionMatrix();
        void SetViewOffset(double fullWidth, double fullHeight, double offsetX, double offsetY, double width, double height);
        void ClearViewOffset();
        virtual std::string ToJson() const;
    public:
        double zoom;
        std::shared_ptr<View> view;
        double left;
        double right;
        double top;
        double buttom;
        double near;
        double far;
    };
} // namespace Three
