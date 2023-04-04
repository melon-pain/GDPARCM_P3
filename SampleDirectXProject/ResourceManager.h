#pragma once
#include <unordered_map>
#include <string>
#include "Prerequisites.h"
#include "Resource.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Resource* CreateResourceFromFile(const wchar_t* file_path);

protected:
	virtual Resource* CreateResourceFromFileConcerete(const wchar_t* file_path) = 0;
private:
	std::unordered_map<std::wstring, Resource*> m_map_resources;
};

