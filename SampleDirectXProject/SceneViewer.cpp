#include "SceneViewer.h"
#include "GraphicsEngine.h"
#include "SceneHandler.h"
#include "Scene.h"

#include <iostream>
#include <string>

SceneViewer::SceneViewer() : UIScreen("SceneViewer", true)
{

}

SceneViewer::~SceneViewer()
{
}

void SceneViewer::DrawUI()
{
	ImGui::Begin("Scene Viewer", &isActive);
	// Get all scenes
	std::vector<Scene*> sceneList = SceneHandler::Get()->GetSceneList();
	
	if (sceneList.size() <= 0)
	{
		ImGui::End();
		return;
	}
	
	for (int i = 0; i < sceneList.size(); i++)
	{
		Scene* scene = sceneList[i];

		// Scene name
		std::string sceneNum = std::to_string(i + 1);
		std::string sceneName = "Scene " + sceneNum;
		ImGui::Text(sceneName.c_str());
		SceneState state = scene->GetState();
		switch (state)
		{
		case SceneState::Standby: {
			std::string buttonLabel = "Load Scene " + sceneNum;
			if (ImGui::Button(buttonLabel.c_str()))
			{
				scene->LoadScene();
			}
			ImGui::ProgressBar(0, ImVec2(128, 16), "Ready to load");
		}; break;
		case SceneState::Loading: {
			float progress = scene->GetProgress();
			std::string progressText = std::to_string(progress);
			std::string displayString = baseText + progressText;
			const char* displayChar = displayString.c_str();
			std::string buttonLabel = "Cancel Loading Scene " + sceneNum;
			if (ImGui::Button(buttonLabel.c_str()))
			{
				scene->UnloadScene();
			}
			// Progress range is 0 to 1
			ImGui::ProgressBar(progress, ImVec2(128, 16), displayChar);
		}; break;
		case SceneState::Loaded: {
			std::string buttonLabel = "View Scene " + sceneNum;
			if (ImGui::Button(buttonLabel.c_str()))
			{
				SceneHandler::Get()->ViewScene(i);
			}
			buttonLabel = "Delete Scene " + sceneNum;
			if (ImGui::Button(buttonLabel.c_str()))
			{
				scene->UnloadScene();
			}
			ImGui::ProgressBar(1, ImVec2(128, 16), "Scene loaded");
		}; break;
		}
	}
	if (ImGui::Button("View all scenes"))
	{
		SceneHandler::Get()->ViewAllScene();
	}
	
	ImGui::End();
}
