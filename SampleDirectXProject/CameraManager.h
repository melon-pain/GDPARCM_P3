#pragma once

#include <vector>

class Camera;
class CameraManager
{
public:
	CameraManager();

public:
	static void Initialize();

private:
	static CameraManager* instance;
public:
	static CameraManager* Get();

private:
	std::vector<Camera*> cameraList;
	Camera* activeCamera = nullptr;

public:
	Camera* InstantiateCamera(bool setActive = false);
	void DestroyCamera(Camera* camera);
public:
	Camera* GetActiveCamera() const;
	void SetActiveCamera(Camera* camera);
};
