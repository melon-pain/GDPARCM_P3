#include "ObjectParentingScreen.h"

ObjectParentingScreen::ObjectParentingScreen() : UIScreen("ObjectParenting", true)
{
}

ObjectParentingScreen::~ObjectParentingScreen()
{
}

void ObjectParentingScreen::DrawUI()
{
	ImGui::Begin("Object Parenting", &isActive);
	if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
	{
		InputSystem::get()->ConsumeLeftMouseButton();
	}

	GameObject* selectedObj = GameObjectManager::Get()->GetSelectedGameObject();
	
	//String selectedObjTxt = "Selected Object: " + ((selectedObj == nullptr) ? "N/A" : selectedObj->GetName());
	//ImGui::Text(selectedObjTxt.c_str());

	if (selectedObj != nullptr)
	{
		// Display Current Parent
		String currParentText = "Current Parent: " + ((selectedObj->GetParent() == nullptr) ? "N/A" : selectedObj->GetParent()->GetName());
		ImGui::Text(currParentText.c_str());
		// Display Detach Button
		if (selectedObj->GetParent() != nullptr)
		{
			if (ImGui::Button("Detach from Parent"))
			{
				selectedObj->RemoveFromParent();
			}
		}

		// Display list of game objects to parent
		static String objToParentName = "";
		
		unordered_map<String, GameObject*> gameObjsMap;
		vector<GameObject*> gameObjList = GameObjectManager::Get()->GetGameObjectList();

		for (int i = 0; i < gameObjList.size(); i++)
		{
			GameObject* obj = gameObjList[i];
			// Continue if same object
			if (selectedObj == obj) continue; 
			
			if (selectedObj->GetParent() != nullptr && selectedObj->GetParent() == obj) continue;

			gameObjsMap.emplace(obj->GetName(), gameObjList[i]);
		}

		ImGui::Dummy(ImVec2(0.0f, 10.0f));
		// Display root parent objects
		if (ImGui::BeginCombo("Select Parent", objToParentName.c_str()))
		{
			for (pair<String, GameObject*> it : gameObjsMap)
			{
				bool isSelected = objToParentName == it.first.c_str();

				if (ImGui::Selectable(it.first.c_str(), isSelected))
				{
					objToParentName = it.first;
				}
					
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		if (ImGui::Button("Set Parent"))
		{
			// Set Parent
			GameObject* objToParent = gameObjsMap[objToParentName];
			if (objToParent != nullptr)
			{
				selectedObj->SetParent(gameObjsMap[objToParentName]);
				objToParentName = "";
			}
		}
	}

	ImGui::End();
}

void ObjectParentingScreen::CreateComboObj(GameObject* obj)
{
}
