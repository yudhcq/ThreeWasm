#pragma once
#include "../Math/Matrix4.h"
#include "../Core/Object3D.h"

namespace Three
{
	class Camera: public Object3D
	{
	public:
		Camera();
		virtual Vector3 GetWorldDirection() const;
		virtual void UpdateMatrixWorld(bool force = false);
	public:
		Matrix4 matrixWorldInverse;
		Matrix4 projectionMatrix;
		Matrix4 projectionMatrixInverse;
	};
} // namespace Camera
