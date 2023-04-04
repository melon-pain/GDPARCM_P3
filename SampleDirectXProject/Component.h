#pragma once

class GameObject;
class Component
{
public:
	Component();
	virtual ~Component();

public:
	virtual void Start();
	virtual void Update(float deltaTime);

public:
	GameObject* GetOwner() const;
	void SetOwner(GameObject* _owner);

protected:
	GameObject* m_owner = nullptr;
	bool m_has_started = false;
};

