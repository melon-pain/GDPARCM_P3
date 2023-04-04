#include "TransformComponent.h"
#include "MeshComponent.h"
#include "GameObject.h"
#include <iostream>

TransformComponent::TransformComponent() : Component()
{
	m_position = Vector3::Zero;
	m_scale = Vector3::One;

	transformMatrix = Matrix::Identity;
}

TransformComponent::~TransformComponent() = default;

Vector3 TransformComponent::GetPosition() const
{
	return m_position;
}

Vector3 TransformComponent::GetEulerAngles() const
{
	return m_euler_angles;
}

Quaternion TransformComponent::GetRotation() const
{
	return m_rotation;
}

Vector3 TransformComponent::GetScale() const
{
	return m_scale;
}

void TransformComponent::SetPosition(const Vector3& _position)
{
	m_position = _position;
	UpdateTransformMatrix();
}
 
void TransformComponent::SetEulerAngles(const Vector3& _angles)
{
	m_euler_angles = _angles;
	m_rotation = Quaternion::CreateFromYawPitchRoll(_angles);
	UpdateTransformMatrix();
}

void TransformComponent::SetRotation(const Quaternion& _rotation)
{
	m_rotation = _rotation;
	m_euler_angles = _rotation.ToEuler();
	UpdateTransformMatrix();
}

void TransformComponent::SetScale(const Vector3& _scale)
{
	m_scale = _scale;
	UpdateTransformMatrix();
}

void TransformComponent::UpdateTransformMatrix()
{
	Matrix temp;

	transformMatrix = Matrix::Identity;

	temp = Matrix::Identity;
	temp = Matrix::CreateScale(m_scale);
	transformMatrix *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateFromQuaternion(m_rotation);
	transformMatrix *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateTranslation(m_position);
	transformMatrix *= temp;
}

Matrix TransformComponent::GetTransformationMatrix()
{
	return transformMatrix;
}

Matrix TransformComponent::GetLocalToWorldMatrix() const
{
	Matrix worldMatrix = transformMatrix;

	GameObject* current = this->GetOwner();

	while (GameObject* parent = current->GetParent())
	{
		current = parent;
		worldMatrix *= current->GetTransform()->GetTransformationMatrix();
	}

	return worldMatrix;
}

Matrix TransformComponent::GetWorldToLocalMatrix() const
{
	Matrix invWorld = GetLocalToWorldMatrix().Invert();
	return invWorld;
}

float* TransformComponent::GetPhysicsMatrix()
{
	Matrix temp;

	Matrix phys = Matrix::Identity;

	temp = Matrix::Identity;
	temp = Matrix::CreateScale(Vector3::One);
	phys *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateFromQuaternion(m_rotation);
	phys *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateTranslation(m_position);
	phys *= temp;
	
	float* m = new float[16]
	{
		phys._11, phys._12, phys._13, phys._14,
		phys._21, phys._22, phys._23, phys._24,
		phys._31, phys._32, phys._33, -	phys._34,
		phys._41, phys._42, phys._43, phys._44
	};

	return m;
}

void TransformComponent::SetPhysicsMatrix(float* mat)
{
	Matrix m = Matrix(mat);
	Vector3 s;

	m.Decompose(s, m_rotation, m_position);
	m_rotation = -m_rotation;
	m_euler_angles = m_rotation.ToEuler();

	//std::cout << "X: " << m_position.x << " Y: " << m_position.y << " Z: " << m_position.z << std::endl;
}

void TransformComponent::SetTransformationMatrix(Matrix m)
{
	transformMatrix = m;

	m.Decompose(m_scale, m_rotation, m_position);
	m_euler_angles = m_rotation.ToEuler();
}