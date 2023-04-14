#include "SceneHandler.h"

SceneHandler* SceneHandler::instance = nullptr;

SceneHandler::SceneHandler()
{

}

SceneHandler::~SceneHandler()
{
	SceneHandler::instance = nullptr;
}

void SceneHandler::Create()
{
	if (SceneHandler::instance) throw std::exception("Scene Handler already created");
	SceneHandler::instance = new SceneHandler();
}

void SceneHandler::RegisterScene(Scene* scene)
{
	sceneList.push_back(scene);
}

void SceneHandler::ViewScene(int sceneIndex)
{
	for (int i = 0; i < sceneList.size(); i++)
	{
		Scene* scene = sceneList[i];
		// Show scene
		if (sceneIndex == i)
			scene->ToggleViewScene(true);
		// Hide scene
		else
			scene->ToggleViewScene(false);
	}
	sceneViewing = sceneIndex;
}

void SceneHandler::ViewAllScene()
{
	for (int i = 0; i < sceneList.size(); i++)
	{
		Scene* scene = sceneList[i];
		scene->ToggleViewScene(true);
	}
	sceneViewing = -1;
}
