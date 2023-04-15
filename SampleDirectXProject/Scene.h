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
		{ L"Assets\\Meshes\\Scene_1\\mario.obj", L"Assets\\Meshes\\Scene_1\\yoshi.obj", L"Assets\\Meshes\\Scene_1\\wario.obj", L"Assets\\Meshes\\Scene_1\\armadillo.obj", L"Assets\\Meshes\\Scene_1\\donkeykong.obj" },
		{ L"Assets\\Meshes\\Scene_2\\bowserkey.obj", L"Assets\\Meshes\\Scene_2\\chomp.obj", L"Assets\\Meshes\\Scene_2\\plant.obj", L"Assets\\Meshes\\Scene_2\\suzanne.obj", L"Assets\\Meshes\\Scene_2\\penguin.obj" },
		{ L"Assets\\Meshes\\Scene_3\\goomba.obj", L"Assets\\Meshes\\Scene_3\\boo.obj", L"Assets\\Meshes\\Scene_3\\mariohead.obj", L"Assets\\Meshes\\Scene_3\\monty.obj", L"Assets\\Meshes\\Scene_3\\statue.obj" },
		{ L"Assets\\Meshes\\Scene_4\\peach.obj", L"Assets\\Meshes\\Scene_4\\star.obj", L"Assets\\Meshes\\Scene_4\\toad.obj", L"Assets\\Meshes\\Scene_4\\teapot.obj", L"Assets\\Meshes\\Scene_4\\koopa.obj" },
		{ L"Assets\\Meshes\\Scene_5\\cornerianfighter.obj", L"Assets\\Meshes\\Scene_5\\bunny.obj", L"Assets\\Meshes\\Scene_5\\invader.obj", L"Assets\\Meshes\\Scene_5\\catspaw.obj", L"Assets\\Meshes\\Scene_5\\bolse.obj" }
	};
};