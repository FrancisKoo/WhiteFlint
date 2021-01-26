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

	// The fucking simple math use right hand by default.
	Vector3 front = Vector3::Backward;
	Matrix yaw = Matrix::CreateRotationY(euler.y);
	front = Vector3::TransformNormal(front, yaw);
	Vector3 right = Vector3::Up.Cross(front);

	Matrix pitch = Matrix::CreateFromAxisAngle(right, euler.x);
	front = Vector3::TransformNormal(front, pitch);

	Vector3 up = front.Cross(right);

	return DirectX::XMMatrixLookToLH(eye, front, up);
}

Matrix Camera::GetProjectionMatrix()
{
	return DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}
