#pragma once
#include "ResourceManager.h"

class Mesh;
class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	Mesh* CreateMeshFromFile(const wchar_t* file_path);
protected:
	// Inherited via ResourceManager
	virtual Resource* CreateResourceFromFileConcerete(const wchar_t* file_path) override;
};

