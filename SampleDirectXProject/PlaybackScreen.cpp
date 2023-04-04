#include "PlaybackScreen.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "EngineBackend.h"

PlaybackScreen::PlaybackScreen() : UIScreen("Playback", true)
{
}

PlaybackScreen::~PlaybackScreen()
{
}

void PlaybackScreen::DrawUI()
{
	EngineBackend* backend = EngineBackend::Get();

	ImGui::Begin("Scene Play Options", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(205, 75));
	ImGui::SameLine();

	//TODO: Use memento pattern for saving state of objects
	if (backend->GetMode() == EditorMode::EDITOR) {
		if (ImGui::Button("Play")) { EngineBackend::Get()->SetMode(EditorMode::PLAY); }
	}

	else if (backend->GetMode() != EditorMode::EDITOR) {
		if (ImGui::Button("Stop")) { EngineBackend::Get()->SetMode(EditorMode::EDITOR); }
	}

	ImGui::SameLine();

	if (backend->GetMode() == EditorMode::PLAY) {
		if (ImGui::Button("Pause")) { EngineBackend::Get()->SetMode(EditorMode::PAUSED); }
	}
	else if (backend->GetMode() == EditorMode::PAUSED) {
		if (ImGui::Button("Resume")) { EngineBackend::Get()->SetMode(EditorMode::PLAY); }
	}

	ImGui::SameLine();
	if (backend->GetMode() == EditorMode::PAUSED && ImGui::Button("Frame Step")) { EngineBackend::Get()->StartFrameStep(); }
	ImGui::End();
}
