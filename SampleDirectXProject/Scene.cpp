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
}

void Scene::LoadScene()
{
	for (int i = 0; i < MODEL_COUNT; i++)
	{
		GameObject* obj = GameObjectManager::Get()->CreateEmpty();

		float X = -2.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.f - -2.f)));
		float Y = -2.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.f - -2.f)));
		float Z = -2.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.f - -2.f)));
		obj->GetTransform()->SetPosition({ X, Y, Z });

		gameObjects.push_back(obj);
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

	gameObjects.clear();
	isLoaded = false;
}

float Scene::GetProgress() const
{
	return (float)count / MODEL_COUNT;
}

void Scene::onFinishedExecution()
{
	// Load models here based on pool
	count++;

	if (count == MODEL_COUNT)
	{
		isLoaded = true;
		for (int i = 0; i < MODEL_COUNT; i++)
		{
			MeshComponent* comp = new MeshComponent();
			Mesh* mesh = GraphicsEngine::get()->getMeshManager()->GetLoadedMesh(pools[pool_index][i].c_str());
			comp->SetMesh(mesh);

			gameObjects[i]->AttachComponent(comp);
		}
	}
}
