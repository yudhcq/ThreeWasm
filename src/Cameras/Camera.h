#pragma once
#include "../Math/Matrix4.h"
#include "../Core/Object3D.h"

namespace Three::Camera
{
	class Camera : public Core::Object3D
	{
	public:
	private:
		Math::Matrix4 mMatrixWorldInverse;
		Math::Matrix4 mProjectionMatrix;
		Math::Matrix4 mProjectionMatrixInverse;
	};
} // namespace Camera
