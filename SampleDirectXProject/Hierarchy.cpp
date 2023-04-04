#include "Hierarchy.h"
#include "GameObjectManager.h"

Hierarchy::Hierarchy() : UIScreen("Hierarchy", true)
{
}

Hierarchy::~Hierarchy()
{
}

void Hierarchy::DrawUI()
{
	// Create ImGui Window;
	ImGui::Begin("Hierarchy", &isActive);

	vector<GameObject*> rootObjs = GameObjectManager::Get()->GetRoots();

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
	if (ImGui::TreeNodeEx("Scene", flags))
	{
		for (int i = 0; i < rootObjs.size(); i++)
		{
			GameObject* obj = rootObjs[i];
			SetupNode(obj);
		}
		ImGui::TreePop();
	}

	ImGui::End();
}

void Hierarchy::SetupNode(GameObject* obj)
{
	vector<GameObject*> children = obj->GetChildren();
	if (children.size() > 0)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

		if (ImGui::TreeNodeEx(obj->GetName().c_str(), flags))
		{
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
			{
				GameObjectManager::Get()->SelectGameObject(obj);
			}
			for (int i = 0; i < children.size(); i++)
			{
				SetupNode(children[i]);
			}
			ImGui::TreePop();
		}
	}
	else
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf;
		if (ImGui::TreeNodeEx(obj->GetName().c_str(), flags))
		{
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
			{
				GameObjectManager::Get()->SelectGameObject(obj);
			}
			ImGui::TreePop();
		}
	}
}

