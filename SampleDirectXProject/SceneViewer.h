#pragma once

#include "UIScreen.h"

class SceneViewer : public UIScreen 
{
public:
	SceneViewer();
	~SceneViewer();
	void DrawUI() override;
private:
	//const std::string baseText = "Progress: ";
};

