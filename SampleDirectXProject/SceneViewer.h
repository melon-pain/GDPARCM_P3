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
	void DisplayPopupProgress(float percent);
	
	std::vector<Scene*> viewedLoadingScenes;

	const float fpsUpdateInterval = 0.1f;
	float fpsTicks = 0.0f;
	float fps = 0.0f;

	int my_image_width = 0;
	int my_image_height = 0;
	
	std::vector<ID3D11ShaderResourceView*> sceneTextures;
};
