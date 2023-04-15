#pragma once
#include "ResourceManager.h"
#include <unordered_map>

class IETSemaphore;
class Mesh;
class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	Mesh* CreateMeshFromFile(const wchar_t* file_path);
	Mesh* GetLoadedMesh(const wchar_t* file_path);
	void UnloadMesh(const wchar_t* file_path);
	IETSemaphore* GetMutex() const;
protected:
	// Inherited via ResourceManager
	virtual Resource* CreateResourceFromFileConcerete(const wchar_t* file_path) override;
	std::unordered_map<const wchar_t*, Mesh*> loadedMeshes;
	IETSemaphore* mutex;
};

