#pragma once

#include "UIScreen.h"
#include <vector>

class Scene;
class SceneViewer : public UIScreen 
{
public:
	SceneViewer();
	~SceneViewer();
	void DrawUI() override;
private:
	//const std::string baseText = "Progress: ";
	void DisplayPopupProgress(float percent);
	
	std::vector<Scene*> viewedLoadingScenes;

	const float fpsUpdateInterval = 0.1f;
	float fpsTicks = 0.0f;
	float fps = 0.0f;
};

