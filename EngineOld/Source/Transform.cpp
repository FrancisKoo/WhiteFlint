#include "pch.h"
#include "Transform.h"

Transform::Transform(Vector3 pos /*= Vector3::Zero*/, Vector3 rot /*= Vector3::Zero*/, Vector3 scl /*= Vector3::One*/) :
	position(pos),
	rotation(rot),
	scale(scl)
{
}

void Transform::Translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void Transform::Rotate(float x, float y, float z)
{
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;
}

void Transform::Scale(float x, float y, float z)
{
	scale.x += x;
	scale.y += y;
	scale.z += z;
}

DirectX::SimpleMath::Vector3 Transform::GetForwardDirection()
{
	Vector3 front(0, 0, 1);

	Vector3 euler = rotation;
	float pitch = euler.x;
	float yaw = euler.y;
	//float roll  = euler.z;

	front.x = DirectX::XMScalarSin(yaw) * DirectX::XMScalarCos(pitch);
	front.y = DirectX::XMScalarSin(pitch);
	front.z = DirectX::XMScalarCos(yaw) * DirectX::XMScalarCos(pitch);

	front.Normalize();

	return front;
}

DirectX::SimpleMath::Vector3 Transform::GetRightDirection()
{
	Vector3 right = Vector3(0, 1, 0).Cross(GetForwardDirection());
	return right;
}

DirectX::SimpleMath::Vector3 Transform::GetUpDirection()
{
	Vector3 up = GetForwardDirection().Cross(GetRightDirection());
	up.Normalize();
	return up;
}

void Transform::MoveForward(float z)
{
	position += GetForwardDirection() * z;
}

void Transform::MoveRight(float x)
{
	position += GetRightDirection() * x;
}

void Transform::MoveUp(float y)
{
	position += GetUpDirection() * y;
}

DirectX::SimpleMath::Matrix Transform::GetModelMatrix()
{
	Matrix t, r, s;
	t = Matrix::CreateTranslation(position);
	r = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	s = Matrix::CreateScale(scale);
	return s * r * t;
}

void Transform::Reset()
{
	position = rotation = Vector3::Zero;
	scale = Vector3::One;
}
