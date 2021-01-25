#include "pch.h"
#include "Camera.h"

Camera::Camera(Vector3 position, Vector3 rotation, float fov, float aspect, float near, float far) :
	m_transform(position, rotation),
	m_fov(fov),
	m_aspectRatio(aspect),
	m_nearPlane(near),
	m_farPlane(far)
{
}

Matrix Camera::GetViewMatrix()
{
	Vector3 eye = m_transform.position;
	Vector3 euler = m_transform.rotation;

	Vector3 front = Vector3::Forward;
	Matrix yaw = Matrix::CreateRotationY(euler.y);
	front = Vector3::TransformNormal(front, yaw);
	Vector3 right = Vector3::Up.Cross(front);

	Matrix pitch = Matrix::CreateFromAxisAngle(right, euler.x);
	front = Vector3::TransformNormal(front, pitch);

	Vector3 up = front.Cross(right);

	return Matrix::CreateLookAt(eye, front, up);
}
