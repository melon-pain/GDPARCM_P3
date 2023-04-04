#include "GameObjectManager.h"
#include "GameObject.h"
#include "EngineTime.h"

#include "MeshComponent.h"

#include "GraphicsEngine.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "EngineBackend.h"
#include "EditorAction.h"
#include <random>

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager::GameObjectManager()
{
    this->physicsCommon = new PhysicsCommon();
    PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 50;
    settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
    this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
}

void GameObjectManager::Initialize()
{
    instance = new GameObjectManager();
}

GameObjectManager* GameObjectManager::Get()
{
    return instance;
}

void GameObjectManager::Update()
{
    const float delta = EngineTime::getDeltaTime();

    if (delta > 0.0f)
    {
        if (EngineBackend::Get()->GetMode() == EditorMode::PLAY || 
            (EngineBackend::Get()->GetMode() == EditorMode::PAUSED && EngineBackend::Get()->InsideFrameStep()))
            physicsWorld->update(delta);
        for (const auto& gameObject : gameObjectList)
        {
            if(gameObject->IsEnable())
				gameObject->Update(delta);
        }
    }
}

void GameObjectManager::CreateGameObject()
{
    GameObject* newObj = GameObject::Instantiate();
    gameObjectList.push_back(newObj);

    SelectGameObject(newObj);
}

GameObject* GameObjectManager::CreateCube()
{
    GameObject* cube = GameObject::Instantiate(NAME_CUBE);
    cube->SetObjectType(PrimitiveType::CUBE);

    if (TransformComponent* transform = cube->GetTransform())
    {
        float rand = std::rand() % 5;
        //transform->SetPosition({ rand, 5, rand });
    }

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\cube.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");
    
    if (mesh)
    {
        MeshComponent* meshComponent = new MeshComponent();
        cube->AttachComponent(meshComponent);
        meshComponent->SetMesh(mesh);
        //meshComponent->SetTexture(texture);
    }

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_CUBE) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        cube->SetName(NAME_CUBE + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(cube);
    gameObjectMap.emplace(cube->GetName(), cube);
    SelectGameObject(cube);

    return cube;
}

void GameObjectManager::CreateCubes(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        GameObject* obj = CreateCube();

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(-2.5f, 2.5f); // define the range

        obj->GetTransform()->SetPosition({ (float)distr(gen), 10.0f + (float)distr(gen), (float)distr(gen) });

        std::uniform_int_distribution<> distr2(-1.f, 1.f); // define the range

        obj->GetTransform()->SetEulerAngles({ (float)distr2(gen), (float)distr2(gen), (float)distr2(gen) });

        PhysicsComponent* physics = new PhysicsComponent();
        obj->AttachComponent(physics);
    }
}

void GameObjectManager::CreatePhysicsCubes(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        GameObject* cube = CreateCube();
        PhysicsComponent* component = new PhysicsComponent();
        cube->AttachComponent(component);

        if (TransformComponent* transform = cube->GetTransform())
        {
            SimpleMath::Vector3 rand_position = SimpleMath::Vector3(((rand() % 200) - 100) / 150.0f, ((rand() % 200) - 100) / 150.0f, ((rand() % 200) - 100) / 150.0f);
            transform->SetPosition(rand_position);
        }
    }
}

GameObject* GameObjectManager::CreatePlane()
{
    GameObject* plane = GameObject::Instantiate(NAME_PLANE);
    plane->SetObjectType(PrimitiveType::PLANE);
    if (TransformComponent* transform = plane->GetTransform())
    {
        //transform->SetScale({ 5, 0.1f, 5 });
    }

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\plane.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");
    

    if (mesh)
    {
        MeshComponent* meshComponent = new MeshComponent();
        plane->AttachComponent(meshComponent);
        meshComponent->SetMesh(mesh);
        //meshComponent->SetTexture(texture);

        /*PhysicsComponent* physics = new PhysicsComponent();
        plane->AttachComponent(physics);
        physics->GetRigidbody()->setType(BodyType::KINEMATIC);*/
    }

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_PLANE) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        plane->SetName(NAME_PLANE + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(plane);
    gameObjectMap.emplace(plane->GetName(), plane);
    SelectGameObject(plane);

    return plane;
}

GameObject* GameObjectManager::CreateSphere()
{
    GameObject* obj = GameObject::Instantiate(NAME_SPHERE);
    obj->SetObjectType(PrimitiveType::SPHERE);
    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\sphere.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\grass.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_SPHERE) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_SPHERE + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);

    return obj;
}

GameObject* GameObjectManager::CreateCapsule()
{
    GameObject* obj = GameObject::Instantiate(NAME_CAPSULE);
    obj->SetObjectType(PrimitiveType::CAPSULE);
    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\capsule.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\grass.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_CAPSULE) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_CAPSULE + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);

    return obj;
}

GameObject* GameObjectManager::CreateCylinder()
{
    GameObject* obj = GameObject::Instantiate(NAME_CYLINDER);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\cylinder.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\grass.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_CYLINDER) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_CYLINDER + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);

    return obj;
}

GameObject* GameObjectManager::FindObjectByName(std::string name)
{
    if (this->gameObjectMap[name] != NULL) {
        return this->gameObjectMap[name];
    }
    else {
        std::cout << "Object " << name << " not found!";
        return nullptr;
    }
}

void GameObjectManager::ApplyEditorAction(EditorAction* action)
{
    GameObject* object = FindObjectByName(action->GetOwnerName());
    if (object != nullptr) {
        //re-apply state
        /*object->recomputeMatrix(action->getStoredMatrix().getMatrix());
        object->setPosition(action->getStorePos());
        object->setRotation(action->getStoredOrientation().x, action->getStoredOrientation().y, action->getStoredOrientation().z);
        object->setScale(action->getStoredScale());*/
        if (TransformComponent* transform = object->GetTransform())
        {
            transform->SetPosition(action->GetStorePos());
            transform->SetRotation(action->GetStoredOrientation());
            transform->SetScale(action->GetStoredScale());
        }
    }
}

void GameObjectManager::CreateTeapot()
{
    GameObject* obj = GameObject::Instantiate(NAME_TEAPOT);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\teapot.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_TEAPOT) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_TEAPOT + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateBunny()
{
    GameObject* obj = GameObject::Instantiate(NAME_BUNNY);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\bunny.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\ground.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_BUNNY) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_BUNNY + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateArmadillo()
{
    GameObject* obj = GameObject::Instantiate(NAME_ARMADILLO);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\armadillo.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\grass.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_ARMADILLO) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_ARMADILLO + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateLucy()
{
    GameObject* obj = GameObject::Instantiate(NAME_LUCY);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\statue.obj");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_LUCY) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_LUCY + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateObjectFromFile(std::string name, PrimitiveType type, SimpleMath::Vector3 position, SimpleMath::Vector3 rotation, SimpleMath::Vector3 scale, bool hasPhysics)
{
    GameObject* obj = nullptr;

    switch (type)
    {
    case PrimitiveType::CUBE:
        obj = CreateCube();
        break;
    case PrimitiveType::SPHERE:
        obj = CreateSphere();
        break;
    case PrimitiveType::PLANE:
        obj = CreatePlane();
        break;
    case PrimitiveType::CAPSULE:
        obj = CreateCapsule();
        break;
    }

    obj->GetTransform()->SetPosition(position);
    obj->GetTransform()->SetEulerAngles(rotation);
    obj->GetTransform()->SetScale(scale);

    if (hasPhysics)
    {
        PhysicsComponent* physics = new PhysicsComponent();
        obj->AttachComponent(physics);
    }
}

void GameObjectManager::SaveEditStates()
{
    for (auto* obj : gameObjectList)
    {
        obj->SaveEditState();
    }
}

void GameObjectManager::RestoreEditStates()
{
    for (auto* obj : gameObjectList)
    {
        obj->RestoreEditState();
    }
}

void GameObjectManager::SelectGameObject(GameObject* inObj)
{
    selectedObj = inObj;

    if (MeshComponent* mesh = selectedObj->GetComponent<MeshComponent>())
        mesh->SetOutlined(true);
}

GameObject* GameObjectManager::GetSelectedGameObject() const
{
    return selectedObj;
}

const std::vector<GameObject*>& GameObjectManager::GetGameObjectList() const
{
    return gameObjectList;
}

const std::vector<GameObject*> GameObjectManager::GetRoots() const
{
    std::vector<GameObject*> roots;

    for (const auto& gameObject : gameObjectList)
    {
        if (gameObject->IsRoot())
            roots.push_back(gameObject);
    }

    return roots;
}

PhysicsWorld* GameObjectManager::GetPhysicsWorld()
{
    return physicsWorld;
}

PhysicsCommon* GameObjectManager::GetPhysicsCommon()
{
    return physicsCommon;
}
