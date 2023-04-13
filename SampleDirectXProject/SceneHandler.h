#pragma once

#include "Scene.h"
#include <vector>

class SceneHandler
{
public:
	SceneHandler();
	~SceneHandler();
	void Create();
public:
	static SceneHandler* Get() { return instance; };
	
	void RegisterScene(Scene* scene);
	void ViewScene(int sceneIndex);
	void ViewAllScene();
	std::vector<Scene*> GetSceneList() { return sceneList; };

private:
	static SceneHandler* instance;

	std::vector<Scene*> sceneList;
};

