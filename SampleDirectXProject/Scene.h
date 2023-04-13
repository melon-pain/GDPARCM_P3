#pragma once
#include "IExecutionEvent.h"
#include <vector>
#include <string>

enum class SceneState {
	Standby,
	Loading,
	Loaded
};

class ThreadPool;
class GameObject;
class Scene : public IExecutionEvent
{
public:
	
public:
	Scene(int _pool);
	virtual void LoadScene();
	void UnloadScene();
	void ToggleViewScene(bool flag);

	float GetProgress() const;
	SceneState GetState() const;

private:
	ThreadPool* threadPool;

	int pool_index;
	std::vector<GameObject*> gameObjects;
	bool isLoaded = false;
	int count = 0;
	const int MODEL_COUNT = 5;

	SceneState state = SceneState::Standby;

	// Inherited via IExecutionEvent
	virtual void onFinishedExecution() override;

	const std::wstring pools[5][5] =
	{
		{ L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj" },
		{ L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj" },
		{ L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj" },
		{ L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj" },
		{ L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj", L"Assets\\Meshes\\teapot.obj" }
	};
};