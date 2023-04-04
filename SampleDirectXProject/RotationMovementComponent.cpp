#include "RotationMovementComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

#include <iostream>

RotationMovementComponent::RotationMovementComponent()
{
}

RotationMovementComponent::~RotationMovementComponent()
{
}

void RotationMovementComponent::Start()
{
	Component::Start();
}

void RotationMovementComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	if (!GetOwner())
		return;

	TransformComponent* transform = GetOwner()->GetTransform();

	if (!transform)
		return;

	const SimpleMath::Vector3 currentRotation = transform->GetEulerAngles();
	const SimpleMath::Vector3 newRotation = currentRotation + (axis * m_rotation_rate);

	transform->SetEulerAngles(newRotation);
}

void RotationMovementComponent::SetAxis(const SimpleMath::Vector3& inAxis)
{
	axis = inAxis;
}

void RotationMovementComponent::SetRotationRate(const float& inRate)
{
	m_rotation_rate = inRate;
}
