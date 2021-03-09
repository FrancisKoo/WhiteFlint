#include "pch.h"
#include "Camera.h"

Camera::Camera(Vector3 position, Vector3 rotation, float fov, float aspect, float nearZ, float farZ) :
	m_transform(position, rotation),
	m_fov(fov),
	m_aspectRatio(aspect),
	m_nearPlane(nearZ),
	m_farPlane(farZ)
{
}

Matrix Camera::GetViewMatrix()
{
	Vector3 eye = m_transform.position;
	Vector3 front = m_transform.GetForwardDirection();
	Vector3 target = eye + front;
	
	Vector3 up(0, 1, 0);

	using namespace DirectX;
	Matrix R;
	XMVECTOR eyev = XMLoadFloat3(&eye);
	XMVECTOR targetv = XMLoadFloat3(&target);
	XMVECTOR upv = XMLoadFloat3(&up);
	XMStoreFloat4x4(&R, XMMatrixLookAtLH(eyev, targetv, upv));
	return R;
}

Matrix Camera::GetProjectionMatrix()
{
	using namespace DirectX;
	Matrix R;
	XMStoreFloat4x4(&R, XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane));
	return R;
}
