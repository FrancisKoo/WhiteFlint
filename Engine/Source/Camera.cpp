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
	Vector3 euler = m_transform.rotation;

	Vector3 front = m_transform.GetForwardDirection();
	Vector3 up(0, 1, 0);

	return DirectX::XMMatrixLookAtLH(eye, eye + front, up);
}

Matrix Camera::GetProjectionMatrix()
{
	return DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}
