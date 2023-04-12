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

	if (sceneList.size() > 0)
	{
		for (int i = 0; i < sceneList.size(); i++)
		{
			Scene* scene = sceneList[i];

			// Scene name
			std::string sceneName = "Scene " + std::to_string(i);
			ImGui::Text(sceneName.c_str());
			SceneState state = scene->GetState();
			switch (scene->GetState())
			{
			case SceneState::Standby: {
				ImGui::ProgressBar(0, ImVec2(128, 16), "Ready to load");
			}; break;
			case SceneState::Loading: {
				float progress = scene->GetProgress();
				std::string progressText = std::to_string(progress);
				std::string displayString = baseText + progressText;
				const char* displayChar = displayString.c_str();
				// Progress range is 0 to 1
				ImGui::ProgressBar(progress, ImVec2(128, 16), displayChar);
			}; break;
			case SceneState::Loaded: {
				if (ImGui::Button("Delete Scene"))
				{
					ImGui::ProgressBar(1, ImVec2(128, 16), "Scene loaded");
				}
			}; break;
			}
		}
	}
	
	ImGui::End();
}