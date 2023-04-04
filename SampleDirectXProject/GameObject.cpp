#include "GameObject.h"
#include "Component.h"
#include "TransformComponent.h"
#include "EditorAction.h"

GameObject::GameObject()
{
	transform = new TransformComponent();
	AttachComponent(transform);
}

GameObject::~GameObject()
{
	for(int i = 0; i < m_components.size(); i++)
	{
		delete m_components[i];
	}

	m_components.clear();
}

void GameObject::AttachChild(GameObject* _child)
{
	_child->m_parent = this;
	m_children.push_back(_child);

	//SimpleMath::Vector3 pos = _child->transform->GetPosition();
	
	//const SimpleMath::Matrix m = _child->transform->GetTransformationMatrix() * this->transform->GetWorldToLocalMatrix();
	//_child->transform->SetTransformationMatrix(m);
}

void GameObject::DetachChild(GameObject* _child)
{
	//const SimpleMath::Matrix m = _child->transform->GetTransformationMatrix() * this->transform->GetLocalToWorldMatrix();
	//_child->transform->SetTransformationMatrix(m);

	auto i = std::remove(m_children.begin(), m_children.end(), _child);
	if (i != m_children.end())
	{
		m_children.erase(i);
		_child->m_parent = nullptr;
	}
}

void GameObject::RemoveFromParent()
{
	if (m_parent)
	{
		m_parent->DetachChild(this);
	}
}

bool GameObject::IsChildOf(GameObject* _parent)
{
	return std::count(_parent->m_children.begin(), _parent->m_children.end(), this);
}

void GameObject::AttachComponent(Component* _component)
{
	_component->SetOwner(this);
	_component->Start();
	m_components.push_back(_component);
}

void GameObject::DetachComponent(Component* _component)
{
	_component->SetOwner(nullptr);
	//auto j = remove(m_components.begin(), m_components.end(), _component);
	int toRemoveIndex = 0;
	bool componentFound = false;
	for (int i = 0; i < m_components.size(); i++)
	{
		if (m_components[i] == _component)
		{
			toRemoveIndex = i;
			componentFound = true;
			break;
		}
	}

	if (componentFound)
		m_components.erase(m_components.begin() + toRemoveIndex);
}


bool GameObject::IsRoot() const
{
	return !m_parent;
}

std::string GameObject::GetName() const
{
	return name;
}

void GameObject::SetName(const std::string& _name)
{
	name = _name;
}

GameObject* GameObject::GetRoot() const
{
	GameObject* current = nullptr;

	while (GameObject* parent = this->GetParent())
	{
		current = parent;
	}

	return current;
}

GameObject* GameObject::GetParent() const
{
	return m_parent;
}

std::vector<GameObject*> GameObject::GetChildren() const
{
	return m_children;
}

void GameObject::SetParent(GameObject* _parent) 
{
	// If incoming parent is a child, then don't
	if (std::find(m_children.begin(), m_children.end(), _parent) != m_children.end())
	{
		return;
	}

	this->RemoveFromParent();
	m_parent = _parent;
	m_parent->AttachChild(this);
}

void GameObject::Start()
{
	for (auto* component : m_components)
	{
		component->Start();
	}

	for (auto* child : m_children)
	{
		child->Start();
	}
}

void GameObject::Update(float deltaTime)
{
	for (auto* component : m_components)
	{
		component->Update(deltaTime);
	}

	for (auto* child : m_children)
	{
		child->Update(deltaTime);
	}
}

TransformComponent* GameObject::GetTransform() const
{
	return transform;
}

void GameObject::SaveEditState()
{
	if (lastEditState == nullptr)
	{
		lastEditState = new EditorAction(this);
	}
}

void GameObject::RestoreEditState()
{
	if (lastEditState != nullptr)
	{
		if (transform)
		{
			transform->SetPosition(lastEditState->GetStorePos());
			transform->SetRotation(lastEditState->GetStoredOrientation());
			transform->SetScale(lastEditState->GetStoredScale());
			transform->SetTransformationMatrix(lastEditState->GetStoredMatrix());

			lastEditState = nullptr;
		}
	}
}

PrimitiveType GameObject::GetObjectType() const
{
	return objectType;
}

void GameObject::SetObjectType(PrimitiveType type)
{
	objectType = type;
}

void GameObject::SetEnable(bool value)
{
	isEnable = value;
}

bool GameObject::IsEnable()
{
	return isEnable;
}

GameObject* GameObject::Instantiate()
{
	GameObject* obj = new GameObject();
	obj->Start();
	return obj;
}

GameObject* GameObject::Instantiate(std::string _name)
{
	GameObject* obj = new GameObject();
	obj->Start();
	obj->SetName(_name);
	return obj;
}
