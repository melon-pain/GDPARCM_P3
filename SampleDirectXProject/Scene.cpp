#include "Scene.h"
#include "GraphicsEngine.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "TransformComponent.h"
#include "MeshLoader.h"
#include "MeshManager.h"
#include "MeshComponent.h"
#include "ThreadPool.h"
#include "Mesh.h"

Scene::Scene(int _pool) : pool_index(_pool)
{
	this->threadPool = new ThreadPool("ThreadPool_"+std::to_string(_pool), MODEL_COUNT);
	this->threadPool->startScheduler();
	this->state = SceneState::Standby;
}

void Scene::LoadScene()
{
	this->state = SceneState::Loading;
	count = 0;

	for (int i = 0; i < MODEL_COUNT; i++)
	{
		GameObject* obj = GameObjectManager::Get()->CreateEmpty();
		obj->SetEnable(false);

		float X = -2.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.f - -2.f)));
		float Y = -2.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.f - -2.f)));
		float Z = -2.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.f - -2.f)));
		obj->GetTransform()->SetPosition({ X, Y, Z });

		gameObjects.push_back(obj);

		MeshComponent* mesh = new MeshComponent();
		obj->AttachComponent(mesh);
	}

	// Load models here based on pool
	for (int i = 0; i < MODEL_COUNT; i++)
	{
		MeshLoader* loader = new MeshLoader(pools[pool_index][i], this);
		this->threadPool->scheduleTask(loader);
	}
}

void Scene::UnloadScene()
{
	for (GameObject* gameObject : gameObjects)
	{
		GameObjectManager::Get()->DestroyGameObject(gameObject);
	}

	for (int i = 0; i < MODEL_COUNT; i++)
	{
		GraphicsEngine::get()->getMeshManager()->UnloadMesh(pools[pool_index][i].c_str());
	}

	gameObjects.clear();
	isLoaded = false;
	this->state = SceneState::Standby;
}

void Scene::ToggleViewScene(bool flag)
{
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->SetEnable(flag);
	}
}

float Scene::GetProgress() const
{
	return (float)count / MODEL_COUNT;
}

SceneState Scene::GetState() const
{
	return state;
}

void Scene::onFinishedExecution()
{
	// Load models here based on pool
	count++;

	if (count == MODEL_COUNT)
	{
		isLoaded = true;
		for (int i = 0; i < gameObjects.size(); i++)
		{
			Mesh* mesh = GraphicsEngine::get()->getMeshManager()->GetLoadedMesh(pools[pool_index][i].c_str());
			gameObjects[i]->GetComponent<MeshComponent>()->SetMesh(mesh);
		}
		this->state = SceneState::Loaded;
	}
}
