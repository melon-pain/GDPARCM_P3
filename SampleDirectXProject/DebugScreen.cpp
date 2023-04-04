#include "DebugScreen.h"

DebugScreen::DebugScreen() : UIScreen("DebugScreen", true)
{
}

DebugScreen::~DebugScreen()
{
}

void DebugScreen::DrawUI()
{
	if (ImGui::Button("Clear"))
	{
		ClearLogs();
	}
	for (size_t i = 0; i < logs.size(); i++)
	{
		ImGui::Text(logs[i].c_str());
	}
}

void DebugScreen::AddLog(std::string log)
{
	logs.push_back(log);
}

void DebugScreen::ClearLogs()
{
	logs.clear();
}
