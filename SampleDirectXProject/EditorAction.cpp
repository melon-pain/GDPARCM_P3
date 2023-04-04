#include "EditorAction.h"
#include "TransformComponent.h"

EditorAction::EditorAction(GameObject* gameObject)
{
	this->objectName = gameObject->GetName();
	if (TransformComponent* transform = gameObject->GetComponent<TransformComponent>())
	{
		this->localPosition = transform->GetPosition();
		this->orientation = transform->GetRotation();
		this->localScale = transform->GetScale();
		this->localMatrix = transform->GetTransformationMatrix();
	}
}
	

EditorAction::~EditorAction()
{
}

std::string EditorAction::GetOwnerName() const
{
    return objectName;
}

SimpleMath::Vector3 EditorAction::GetStorePos() const
{
    return localPosition;
}

SimpleMath::Vector3 EditorAction::GetStoredScale() const
{
    return localScale;
}

SimpleMath::Quaternion EditorAction::GetStoredOrientation() const
{
    return orientation;
}

SimpleMath::Matrix EditorAction::GetStoredMatrix() const
{
    return localMatrix;
}
