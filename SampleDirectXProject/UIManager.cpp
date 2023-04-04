#include "UIManager.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::Get()
{
	return sharedInstance;
}

void UIManager::Initialize(HWND hwnd)
{
	sharedInstance = new UIManager(hwnd);
}

void UIManager::Destroy()
{
}

void UIManager::ToggleUI(String name)
{
	if (this->uiTable[name] != nullptr)
	{
		bool isActive = this->uiTable[name]->GetActive();
		this->uiTable[name]->SetActive(!isActive);
	}
}

void UIManager::DrawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size(); i++)
	{
		this->uiList[i]->Update();
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND hwnd)
{
	// Initialize
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)(io);

	// Style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getRenderSystem()->getDevice(), GraphicsEngine::get()->getRenderSystem()->getID3D11DeviceContext());

	// Populate UI Table
	UINames uiNames;
	MenuBar* menuBar = new MenuBar();
	this->uiTable[uiNames.MENU_BAR] = menuBar;
	this->uiList.push_back(menuBar);

	ObjectProperty* objProp = new ObjectProperty();
	this->uiTable[uiNames.OBJECT_PROPERTY] = objProp;
	this->uiList.push_back(objProp);

	ObjectParentingScreen* objParenting = new ObjectParentingScreen();
	this->uiTable[uiNames.OBJECT_PARENTING] = objParenting;
	this->uiList.push_back(objParenting);

	Hierarchy* hierarchy = new Hierarchy();
	this->uiTable[uiNames.HIERARCHY] = hierarchy;
	this->uiList.push_back(hierarchy);

	CreditsScreen* credits = new CreditsScreen();
	this->uiTable[uiNames.CREDITS_SCREEN] = credits;
	this->uiList.push_back(credits);

	PlaybackScreen* playback = new PlaybackScreen();
	this->uiTable[uiNames.PLAYBACK] = playback;
	this->uiList.push_back(playback);

	ActionScreen* action = new ActionScreen();
	this->uiTable[uiNames.ACTION] = action;
	this->uiList.push_back(action);

	DebugScreen* debug = new DebugScreen();
	this->uiTable[uiNames.DEBUG] = debug;
	this->uiList.push_back(debug);
}

UIManager::~UIManager()
{
}
