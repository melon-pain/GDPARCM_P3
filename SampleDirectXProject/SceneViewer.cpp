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
	
	int sceneViewing = SceneHandler::Get()->GetSceneViewed();
	
	std::string sceneViewingString = "Current Scene: " + ((sceneViewing == -1) ? "All" : std::to_string(sceneViewing + 1));
	ImGui::Text(sceneViewingString.c_str());
	
	std::string fpsString = "FPS: ";
	ImGui::Text(fpsString.c_str());

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
		std::string sceneName = "----- Scene " + sceneNum + " -----";
		ImGui::Text(sceneName.c_str());
		SceneState state = scene->GetState();
		switch (state)
		{
			case SceneState::Standby: {
				// Progress Bar
				ImGui::ProgressBar(0, ImVec2(128, 16), "Ready to load");
				// Button 1
				std::string buttonLabel = "Load Scene " + sceneNum;
				if (ImGui::Button(buttonLabel.c_str()))
					scene->LoadScene();
				// Spacing
				ImGui::Dummy(ImVec2(0.0f, 16.0f));
			}; break;
			case SceneState::Loading: {
				// Progress Bar
				float progress = scene->GetProgress();
				std::string progressText = std::to_string(int(progress * 100));
				std::string displayString = progressText + "%";
				const char* displayChar = displayString.c_str();
				// Progress range is 0 to 1
				ImGui::ProgressBar(progress, ImVec2(128, 16), displayChar);
				// Button 1
				std::string viewButtonLabel = "View Scene " + sceneNum;
				if (ImGui::Button(viewButtonLabel.c_str()))
					scene->ToggleViewScene(true);
				// Button 2
				std::string cancelButtonLabel = "Cancel Loading Scene " + sceneNum;
				if (ImGui::Button(cancelButtonLabel.c_str()))
					scene->UnloadScene();
			}; break;
			case SceneState::Loaded: {
				// Progress Bar
				ImGui::ProgressBar(1, ImVec2(128, 16), "Scene loaded");
				// Button 1
				std::string buttonLabel = "View Scene " + sceneNum;
				if (ImGui::Button(buttonLabel.c_str()))
					scene->ToggleViewScene(true);
				// Button 2
				buttonLabel = "Delete Scene " + sceneNum;
				if (ImGui::Button(buttonLabel.c_str()))
					scene->UnloadScene();

			}; break;
		}
	}
	ImGui::Text("-------------------");
	if (ImGui::Button("View all scenes"))
		SceneHandler::Get()->ViewAllScene();
	
	ImGui::End();
}
