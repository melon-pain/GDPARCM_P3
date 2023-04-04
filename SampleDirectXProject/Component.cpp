#include "Component.h"

Component::Component()
{
}

Component::~Component()
{
}

void Component::Start()
{
	if (m_has_started)
		return;
	m_has_started = true;
}

void Component::Update(float deltaTime)
{
}

GameObject* Component::GetOwner() const
{
	return m_owner;
}

void Component::SetOwner(GameObject* _owner)
{
	m_owner = _owner;
}
