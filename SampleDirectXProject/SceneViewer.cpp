#include "SceneViewer.h"
#include "GraphicsEngine.h"
#include "SceneHandler.h"
#include "Scene.h"
#include "AppWindow.h"
#include "EngineTime.h"

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
	
	if (viewedLoadingScenes.size() > 0)
	{
		int viewCount = 0;
		float progress = 0.0f;

		for (int i = viewedLoadingScenes.size() - 1; i >= 0; i--)
		{
			Scene* scene = viewedLoadingScenes[i];
			if (scene->GetState() == SceneState::Loaded)
			{
				viewedLoadingScenes.erase(viewedLoadingScenes.begin() + i);
				continue;
			}
				
			progress += scene->GetProgress();
			viewCount++;
		}

		DisplayPopupProgress(progress /= viewCount);
	}
	// Scene View
	int sceneViewing = SceneHandler::Get()->GetSceneViewed();
	std::string sceneSuffix = "";
	if (sceneViewing == -2)
		sceneSuffix = "N/A";
	else if (sceneViewing == -1)
		sceneSuffix = "All";
	else
		sceneSuffix = std::to_string(sceneViewing + 1);
		
	std::string sceneViewingString = "Current Scene: " + sceneSuffix;
	ImGui::Text(sceneViewingString.c_str());
	// FPS
	fpsTicks += EngineTime::getDeltaTime();
	if (fpsTicks >= fpsUpdateInterval)
	{
		fps = AppWindow::Get()->getFPS();
		fpsTicks = 0.0f;
	}
	
	std::string fpsString = "FPS: " + std::to_string((int)fps);
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
				{
					scene->LoadScene();
					SceneHandler::Get()->ViewScene(i);
					viewedLoadingScenes.clear();
					viewedLoadingScenes.push_back(scene);
				}
					
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
				{
					SceneHandler::Get()->ViewScene(i);
					viewedLoadingScenes.clear();
					viewedLoadingScenes.push_back(scene);
				}
					
				// Button 2
				std::string cancelButtonLabel = "Cancel Loading Scene " + sceneNum;
				if (ImGui::Button(cancelButtonLabel.c_str()))
				{
					if (SceneHandler::Get()->GetSceneViewed() == i)
					{
						SceneHandler::Get()->UnviewScene();
						viewedLoadingScenes.clear();
					}
					scene->UnloadScene();
				}
			}; break;
			case SceneState::Loaded: {
				// Progress Bar
				ImGui::ProgressBar(1, ImVec2(128, 16), "Scene loaded");
				// Button 1
				std::string buttonLabel = "View Scene " + sceneNum;
				if (ImGui::Button(buttonLabel.c_str()))
					SceneHandler::Get()->ViewScene(i);
				// Button 2
				buttonLabel = "Delete Scene " + sceneNum;
				
				if (ImGui::Button(buttonLabel.c_str()))
				{
					if (SceneHandler::Get()->GetSceneViewed() == i)
					{
						SceneHandler::Get()->UnviewScene();
					}
					scene->UnloadScene();
				}
			}; break;
		}
	}
	ImGui::Text("-------------------");
	if (ImGui::Button("View all scenes"))
	{
		SceneHandler::Get()->ViewAllScene();

		viewedLoadingScenes.clear();
		for (int i = 0; i < sceneList.size(); i++)
		{
			Scene* scene = sceneList[i];
			if (scene->GetState() == SceneState::Loading)
				viewedLoadingScenes.push_back(scene);
		}
	}
		
	ImGui::End();
}

void SceneViewer::DisplayPopupProgress(float percent)
{
	ImGui::Begin("Loading Bar");
	std::string percentString = std::to_string(int(percent * 100)) + "%";
	ImGui::ProgressBar(percent, ImVec2(256, 32), percentString.c_str());
	ImGui::End();
}
