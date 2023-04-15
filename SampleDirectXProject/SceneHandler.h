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
	void UnviewScene();
	void ViewScene(int sceneIndex);
	void ViewAllScene();
	std::vector<Scene*> GetSceneList() { return sceneList; };
	int GetSceneViewed() { return sceneViewing; };
private:
	static SceneHandler* instance;

	std::vector<Scene*> sceneList;
	int sceneViewing = -2; // -2 is none, -1 is view all
};

