#pragma once
#include "Component.h"
#include <functional>

#include "SimpleMath.h"

using namespace DirectX;

class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent() override;

private:
	SimpleMath::Vector3 m_position;
	SimpleMath::Vector3 m_euler_angles;
	SimpleMath::Quaternion m_rotation;
	SimpleMath::Vector3 m_scale;
	SimpleMath::Matrix transformMatrix;

public:
	SimpleMath::Vector3 GetPosition() const;
	SimpleMath::Vector3 GetEulerAngles() const;
	SimpleMath::Quaternion GetRotation() const;
	SimpleMath::Vector3 GetScale() const;

	void SetPosition(const SimpleMath::Vector3& _position);
	void SetEulerAngles(const SimpleMath::Vector3& _angles);
	void SetRotation(const SimpleMath::Quaternion& _rotation);
	void SetScale(const SimpleMath::Vector3& _scale);
public:
	void UpdateTransformMatrix();
	SimpleMath::Matrix GetTransformationMatrix();
	void SetTransformationMatrix(SimpleMath::Matrix m);
	SimpleMath::Matrix GetLocalToWorldMatrix() const;
	SimpleMath::Matrix GetWorldToLocalMatrix() const;
	float* GetPhysicsMatrix();
	void SetPhysicsMatrix(float* mat);
};
