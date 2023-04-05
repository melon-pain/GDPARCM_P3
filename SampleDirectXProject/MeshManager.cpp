#include "MeshManager.h"
#include "Mesh.h"

MeshManager::MeshManager()
{
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
