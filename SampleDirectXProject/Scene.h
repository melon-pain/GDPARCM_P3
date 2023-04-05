#pragma once
#include "IExecutionEvent.h"
#include <vector>
#include <string>

class ThreadPool;
class GameObject;
class Scene : public IExecutionEvent
{
public:
	Scene(int _pool);
	virtual void LoadScene();
	void UnloadScene();

	float GetProgress() const;

private:
	ThreadPool* threadPool;

	int pool_index;
	std::vector<GameObject*> gameObjects;
	bool isLoaded = false;
	int count = 0;
	const int MODEL_COUNT = 5;

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