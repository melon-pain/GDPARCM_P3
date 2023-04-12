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

}
