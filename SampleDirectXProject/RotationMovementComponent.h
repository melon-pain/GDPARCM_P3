#pragma once
#include "Component.h"
#include "SimpleMath.h"

using namespace DirectX;

class RotationMovementComponent : public Component
{
public:
	RotationMovementComponent();
	~RotationMovementComponent() override;
public:
	void Start() override;
	void Update(float deltaTime) override;

public:
	void SetAxis(const SimpleMath::Vector3& inAxis);
	void SetRotationRate(const float& inRate);

protected:
	SimpleMath::Vector3 axis;
	float m_rotation_rate = 360.0f;
};
