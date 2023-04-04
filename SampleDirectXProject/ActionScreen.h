#pragma once
#include "UIScreen.h"

class ActionScreen :public UIScreen
{
	ActionScreen();
	~ActionScreen();

	virtual void DrawUI() override;
	friend class UIManager;
};

