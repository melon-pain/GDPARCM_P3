#include "MeshLoader.h"
#include "MeshManager.h"
#include "GraphicsEngine.h"
#include "IExecutionEvent.h"
#include "IETSemaphore.h"

MeshLoader::MeshLoader(std::wstring path, IExecutionEvent* executionEvent) : Path(path), exec(executionEvent)
{
}

MeshLoader::~MeshLoader()
{
}

void MeshLoader::Interrupt()
{
	isInterrupted = true;
}

void MeshLoader::onStartTask()
{
	GraphicsEngine::get()->getMeshManager()->GetMutex()->acquire();
	GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(Path.c_str());
	if (isInterrupted)
	{
		delete this;
		GraphicsEngine::get()->getMeshManager()->GetMutex()->release();
		return;
	}
	this->exec->onFinishedExecution();
	GraphicsEngine::get()->getMeshManager()->GetMutex()->release();
	//delete after being done
	delete this;
}
