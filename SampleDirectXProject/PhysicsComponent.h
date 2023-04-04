#pragma once
#include "Component.h"

#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;

class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();

public:
	void Start() override;
	void Update(float deltaTime) override;
	RigidBody* GetRigidbody();
	void ChangeBodyType(int type);
	BodyType GetBodyType();
private:
	RigidBody* rigidBody = nullptr;
};

