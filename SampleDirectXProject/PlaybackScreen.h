#pragma once
#include "UIScreen.h"

class PlaybackScreen : public UIScreen
{
	PlaybackScreen();
	~PlaybackScreen();

	virtual void DrawUI() override;
	friend class UIManager;

	bool played = false;
	bool paused = false;
};

