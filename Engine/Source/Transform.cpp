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
