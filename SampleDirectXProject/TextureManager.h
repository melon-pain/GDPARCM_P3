#pragma once
#include "ResourceManager.h"

class TextureManager : public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	class Texture* CreateTextureFromFile(const wchar_t* file_path); 
	class Texture* CreateTextureFromFileAssets(const wchar_t* file_name);
protected:
	// Inherited via ResourceManager
	virtual Resource* CreateResourceFromFileConcerete(const wchar_t* file_path) override;
};

