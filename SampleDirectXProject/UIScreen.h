#pragma once

#include <iostream>
#include <d3d11.h>
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"


typedef std::string String;
class UIManager;

class UIScreen
{
protected:
	typedef std::string String;
	UIScreen(String name, bool isActive);
	~UIScreen();

	String GetName();
	bool GetActive();
	void SetActive(bool isActive);

	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

	void Update();
	virtual void DrawUI() = 0;

	String name;
	bool isActive = true;
	friend class UIManager;
};

