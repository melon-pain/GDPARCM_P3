#include "PhysicsComponent.h"
#include "GameObject.h"
#include "GameObjectManager.h"

#include "TransformComponent.h"
#include "EngineBackend.h"

#include <iostream>

PhysicsComponent::PhysicsComponent()
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Start()
{
	PhysicsCommon* physicsCommon = GameObjectManager::Get()->GetPhysicsCommon();
	PhysicsWorld* physicsWorld = GameObjectManager::Get()->GetPhysicsWorld();

	// Create a rigid body in the world
	SimpleMath::Vector3 pos = this->GetOwner()->GetTransform()->GetPosition();
	SimpleMath::Quaternion rot = this->GetOwner()->GetTransform()->GetRotation();
	SimpleMath::Vector3 scale = this->GetOwner()->GetTransform()->GetScale();

	float* m = this->GetOwner()->GetTransform()->GetPhysicsMatrix();

	//if (scale.y < 1.0f)
		//scale += SimpleMath::Vector3::One * 2.0f;

	//Transform transform; transform.setFromOpenGL(m);
	Transform transform(Vector3(pos.x, pos.y, pos.z), Quaternion::fromEulerAngles(rot.x, rot.y, rot.z));
	transform.setPosition(Vector3(pos.x, pos.y, pos.z));
	transform.setOrientation(Quaternion::fromEulerAngles(Vector3(rot.x, rot.y, rot.z)));
	

	BoxShape* boxShape;
	if (this->GetOwner()->GetObjectType() == PrimitiveType::PLANE)
	{
		boxShape = physicsCommon->createBoxShape(Vector3(scale.x * 5, 0.1f, scale.z * 5));
	}
	else
		boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 2, scale.y /2, scale.z /2)); //half extent
	
	this->rigidBody = physicsWorld->createRigidBody(transform);

	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(1.0f);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	//transform.getOpenGLMatrix(matrix);
	GetOwner()->GetTransform()->SetRotation(SimpleMath::Quaternion(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z, 1));
	GetOwner()->GetTransform()->SetPosition(SimpleMath::Vector3(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z));

	GetOwner()->GetTransform()->SetPhysicsMatrix(matrix);
}

void PhysicsComponent::Update(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float* matrix = new float[16];
	transform.getOpenGLMatrix(matrix);

	if (EngineBackend::Get()->GetMode() == EditorMode::EDITOR)
	{
		auto position = GetOwner()->GetTransform()->GetPosition();
		auto rotation = GetOwner()->GetTransform()->GetRotation();

		reactphysics3d::Transform trans = reactphysics3d::Transform({ position.x, position.y, position.z }, {rotation.x, rotation.y, rotation.z, rotation.w});
		rigidBody->setTransform(trans);
		rigidBody->setLinearVelocity({ 0, 0, 0 });
		return;
	}

	else if (EngineBackend::Get()->GetMode() == EditorMode::PAUSED && EngineBackend::Get()->InsideFrameStep())
	{
		const auto pos = transform.getPosition();

		this->GetOwner()->GetTransform()->SetRotation(SimpleMath::Quaternion(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z, 1));
		this->GetOwner()->GetTransform()->SetPosition(SimpleMath::Vector3(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z));
		std::cout << "frame" << std::endl;
		return;
	}
	const auto pos = transform.getPosition();

	this->GetOwner()->GetTransform()->SetRotation(SimpleMath::Quaternion(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z, 1));
	this->GetOwner()->GetTransform()->SetPosition(SimpleMath::Vector3(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z));

	//GetOwner()->GetTransform()->SetPhysicsMatrix(matrix);
}

RigidBody* PhysicsComponent::GetRigidbody()
{
	return rigidBody;
}

void PhysicsComponent::ChangeBodyType(int type)
{
	if (type == 0)
	{
		this->rigidBody->setType(BodyType::DYNAMIC);
	}
	else if (type == 1)
	{
		this->rigidBody->setType(BodyType::KINEMATIC);
	}
}

BodyType PhysicsComponent::GetBodyType()
{
	return this->rigidBody->getType();
}