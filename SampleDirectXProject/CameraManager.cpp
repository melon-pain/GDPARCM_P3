#include "CameraManager.h"
#include "Camera.h"

CameraManager* CameraManager::instance = nullptr;

CameraManager::CameraManager() = default;

void CameraManager::Initialize()
{
	instance = new CameraManager();
}

CameraManager* CameraManager::Get()
{
	return instance;
}

Camera* CameraManager::InstantiateCamera(bool setActive)
{
	Camera* camera = new Camera();

	// If there's no existing cameras, set the new camera active
	if (cameraList.empty() || setActive)
	{
		SetActiveCamera(camera);
	}

	cameraList.push_back(camera);

	return camera;
}

void CameraManager::DestroyCamera(Camera* camera)
{
	remove(cameraList.begin(), cameraList.end(), camera);
	delete camera;
}

Camera* CameraManager::GetActiveCamera() const
{
	return activeCamera;
}

void CameraManager::SetActiveCamera(Camera* camera)
{
	activeCamera = camera;
}
