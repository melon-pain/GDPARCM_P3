#include "MeshManager.h"
#include "Mesh.h"
#include "IETSemaphore.h"
#include <iostream>

MeshManager::MeshManager()
{
	mutex = new IETSemaphore(1);
}

MeshManager::~MeshManager()
{
}

Mesh* MeshManager::CreateMeshFromFile(const wchar_t* file_path)
{
	return static_cast<Mesh*>(CreateResourceFromFile(file_path));
}

Mesh* MeshManager::GetLoadedMesh(const wchar_t* file_path)
{
	if (loadedMeshes[file_path])
		return loadedMeshes[file_path];
	return CreateMeshFromFile(file_path);
}

void MeshManager::UnloadMesh(const wchar_t* file_path)
{
	if (!loadedMeshes.contains(file_path))
		return;
	delete loadedMeshes[file_path];

	if (loadedMeshes.contains(file_path))
	{
		std::cout << "Delete mesh" << std::endl;
		loadedMeshes.erase(file_path);
	}
}

IETSemaphore* MeshManager::GetMutex() const
{
	return mutex;
}

Resource* MeshManager::CreateResourceFromFileConcerete(const wchar_t* file_path)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(file_path);
	}
	catch (...) {}

	if (mesh)
		loadedMeshes.emplace(file_path, mesh);

	return mesh;
}
