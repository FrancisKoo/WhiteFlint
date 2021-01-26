#pragma once

#include "Transform.h"

using namespace DirectX::SimpleMath;

class Camera
{
public:
	Camera(Vector3 position, Vector3 rotation, float fov, float aspect, float nearZ, float farZ);
	//~Camera();
	Transform m_transform;

	
	float m_fov;
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;
	
	Matrix GetViewMatrix();
	Matrix GetProjectionMatrix();


private:
};

