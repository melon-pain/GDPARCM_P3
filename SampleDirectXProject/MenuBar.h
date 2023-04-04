#pragma once
#include "UIScreen.h"
#include "UIManager.h"
#include "imfilebrowser.h"

class MenuBar : public UIScreen
{
public:
	MenuBar();
	~MenuBar();
	void DrawUI() override;

private:
	ImGui::FileBrowser* saveSceneDialog;
	ImGui::FileBrowser* openSceneDialog;
};

