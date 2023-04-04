#pragma once
#include "GameObject.h"
#include "SimpleMath.h"
#include <string>

using namespace DirectX;

class EditorAction
{
public:
	EditorAction(GameObject* gameObject);
	~EditorAction();

	std::string GetOwnerName() const;
	SimpleMath::Vector3 GetStorePos() const;
	SimpleMath::Vector3 GetStoredScale() const;
	SimpleMath::Quaternion GetStoredOrientation() const;
	SimpleMath::Matrix GetStoredMatrix() const;

private:
	std::string objectName;
	SimpleMath::Vector3 localPosition;
	SimpleMath::Vector3 localScale;
	SimpleMath::Quaternion orientation;
	SimpleMath::Matrix localMatrix;
};

