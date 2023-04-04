#pragma once
#include "UIScreen.h"
class DebugScreen : public UIScreen
{
public:
	DebugScreen();
	~DebugScreen();
	void DrawUI() override;
	void AddLog(std::string log);
	
private:
	std::vector<std::string> logs;
private:
	void ClearLogs();
};

