#include "CameraComponent.h"

#include "Camera.h"
#include "CameraManager.h"
#include "GameObject.h"
#include "TransformComponent.h"

CameraComponent::~CameraComponent()
{
	CameraManager::Get()->DestroyCamera(camera);
}

void CameraComponent::Start()
{
	Component::Start();

	camera = CameraManager::Get()->InstantiateCamera();

	if (camera)
	{
		camera->SetViewMatrix(GetOwner()->GetTransform()->GetLocalToWorldMatrix().Invert());
		camera->SetCameraProjection(CameraProjectionType::Perspective);
	}
}

void CameraComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	UpdateViewMatrix();
	//camera->SetViewMatrix(GetOwner()->GetTransform()->GetWorldMatrix().GetInverse());
}

void CameraComponent::SetActive() const
{
	if (camera)
	{
		CameraManager::Get()->SetActiveCamera(camera);
	}
}

void CameraComponent::UpdateViewMatrix()
{
	camera->SetViewMatrix(GetOwner()->GetTransform()->GetLocalToWorldMatrix().Invert());
}

Camera* CameraComponent::GetCamera() const
{
	return camera;
}
