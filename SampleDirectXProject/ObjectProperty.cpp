#include "ObjectProperty.h"
#include "GameObjectManager.h"
#include "TextureComponent.h"
#include "PhysicsComponent.h"
#include "ActionHistory.h"

ObjectProperty::ObjectProperty() : UIScreen("ObjectProperty", true)
{
	pos = 0;
	rot = 0;
	scale = 0;
}

ObjectProperty::~ObjectProperty()
{
}

const wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

void ObjectProperty::DrawUI()
{
	// Create ImGui Window
	ImGui::Begin("Object Property", &isActive);
	
	GameObject* const& selectedObj = GameObjectManager::Get()->GetSelectedGameObject();
	String selectedObjTxt = "Selected Object: " + ((selectedObj == nullptr) ? "N/A" : selectedObj->GetName());
	ImGui::Text(selectedObjTxt.c_str());

	if (selectedObj != nullptr)
	{
		ImGui::Checkbox("Enabled", &selectedObj->isEnable);

		bool record = false;
		// Object Transform
		TransformComponent* objTransform = selectedObj->GetTransform();

		// Position
		SimpleMath::Vector3 origPos = objTransform->GetPosition();
		pos = new float[3] { origPos.x, origPos.y, origPos.z != 0 ? -origPos.z : 0 };
		if (ImGui::DragFloat3("Position", pos, 0.1f, 0.0f, 0.0f))
		{
			//record = true;
			ActionHistory::Get()->RecordAction(selectedObj);
		}
		objTransform->SetPosition(SimpleMath::Vector3(pos[0], pos[1], -pos[2]));

		if (ImGui::IsItemClicked(0) || (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered()))
		{
			InputSystem::get()->ConsumeLeftMouseButton();
		}

		SimpleMath::Vector3 origRot = objTransform->GetEulerAngles() * RAD_TO_DEG;
		rot = new float[3] { origRot.x, origRot.y, origRot.z };
		if (ImGui::DragFloat3("Rotation", rot, 0.1f, -360.0f, 360.0f))
		{
			//record = true;
			ActionHistory::Get()->RecordAction(selectedObj);
		}
		objTransform->SetEulerAngles(SimpleMath::Vector3(rot[0], rot[1], rot[2]) * DEG_TO_RAD);
		//objTransform->SetRotation(Quaternion(rot[0], rot[1], rot[2], 1.0f));

		if (ImGui::IsItemClicked(0) || (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered()))
		{
			InputSystem::get()->ConsumeLeftMouseButton();
		}

		SimpleMath::Vector3 origScale = objTransform->GetScale();
		scale = new float[3] { origScale.x, origScale.y, origScale.z };
		if (ImGui::DragFloat3("Scale", scale, 0.1f, 0.0f, 0.0f))
		{
			//record = true;
			ActionHistory::Get()->RecordAction(selectedObj);
		}

		objTransform->SetScale(SimpleMath::Vector3(scale[0], scale[1], scale[2]));

		if (ImGui::IsItemClicked(0) || (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered()))
		{
			InputSystem::get()->ConsumeLeftMouseButton();
		}

		// Existing texture component
		if (selectedObj->GetComponent<TextureComponent>() != nullptr)
		{
			if (ImGui::Button("Detach Texture Component"))
			{
				selectedObj->DetachComponent(selectedObj->GetComponent<TextureComponent>());
			}
		}
		else
		{
			static char textureName[128] = "brick.png";
			ImGui::InputText("Texture File Name", textureName, IM_ARRAYSIZE(textureName));
			if (ImGui::Button("Attach Texture Component"))
			{
				const wchar_t* newName = GetWC(textureName);
				TextureComponent* component = new TextureComponent();
				Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFileAssets(newName);
				if (texture != nullptr)
				{
					component->SetTexture(texture);
					selectedObj->AttachComponent(component);
				}
			}
		}

		// Existing physics component
		if (selectedObj->GetComponent<PhysicsComponent>() != NULL)
		{
			if (selectedObj->GetComponent<PhysicsComponent>()->GetBodyType() == reactphysics3d::BodyType::DYNAMIC)
			{
				if (ImGui::Button("Set to Kinematic"))
				{
					selectedObj->GetComponent<PhysicsComponent>()->ChangeBodyType(1);
				}
			}
			else
			{
				if (ImGui::Button("Set to Dynamic"))
				{
					selectedObj->GetComponent<PhysicsComponent>()->ChangeBodyType(0);
				}
			}

			if (ImGui::Button("Detach Physics Component"))
			{
				selectedObj->DetachComponent(selectedObj->GetComponent<PhysicsComponent>());
			}
		}
		else
		{
			if (ImGui::Button("Attach Physics Component"))
			{
				PhysicsComponent* component = new PhysicsComponent();
				selectedObj->AttachComponent(component);
			}
		}
	}

	ImGui::End();
}