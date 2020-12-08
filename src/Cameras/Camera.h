#pragma once
#include "../Math/Matrix4.h"
#include "../Core/Object3D.h"

namespace Three
{
	class Camera: public Object3D
	{
	public:
		virtual Vector3 GetWorldDirection() const;
		virtual void UpdateMatrixWorld(bool force = false);
	private:
		Matrix4 mMatrixWorldInverse;
		Matrix4 mProjectionMatrix;
		Matrix4 mProjectionMatrixInverse;
	};
} // namespace Camera
