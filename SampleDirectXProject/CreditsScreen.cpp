#include "CreditsScreen.h"

CreditsScreen::CreditsScreen() : UIScreen("CreditsScreen", false)
{
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::DrawUI()
{
	ImGui::Begin("Credits", &isActive);
	ImGui::Text("Scene Editor v0.01\n");
	ImGui::Text("Developers:\n\tManalac, Cesar Dominic\n\tNemeno, Ian Joshua\n\tOmalin, James Gabriel\n\tSantos, John Adriel\n");
	ImGui::Text("Acknowledgements: ");
	ImGui::Text("\tPardCode Game Engine Tutorial");
	ImGui::Text("\tSir Neil's GDENG2 Course");
	ImGui::End();
}
