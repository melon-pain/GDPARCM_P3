#include "ActionScreen.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "ActionHistory.h"
#include "GameObjectManager.h"

ActionScreen::ActionScreen() : UIScreen("ActionScreen", true)
{
}

ActionScreen::~ActionScreen()
{
}

void ActionScreen::DrawUI()
{
	ImGui::Begin("Actions", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(205, 75));
	ImGui::SameLine();
	if (ImGui::Button("Undo")) {
		if (ActionHistory::Get()->HasRemainingUndoActions()) {
			GameObjectManager::Get()->ApplyEditorAction(ActionHistory::Get()->UndoAction());
		}

	}
	ImGui::SameLine();
	if (ImGui::Button("Redo")) {
		if (ActionHistory::Get()->HasRemainingRedoActions()) {
			GameObjectManager::Get()->ApplyEditorAction(ActionHistory::Get()->RedoAction());
		}
	}
	ImGui::End();
}
