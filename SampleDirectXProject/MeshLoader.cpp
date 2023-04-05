#include "MeshLoader.h"
#include "MeshManager.h"
#include "GraphicsEngine.h"
#include "IExecutionEvent.h"

MeshLoader::MeshLoader(std::wstring path, IExecutionEvent* executionEvent) : Path(path), exec(executionEvent)
{
}

MeshLoader::~MeshLoader()
{
}

void MeshLoader::onStartTask()
{
	GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(Path.c_str());
	this->exec->onFinishedExecution();
	//delete after being done
	delete this;
}
