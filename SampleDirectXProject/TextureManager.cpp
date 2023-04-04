#include "TextureManager.h"
#include "Texture.h"
#include <wchar.h>
#include <string>
TextureManager::TextureManager(): ResourceManager()
{
}

TextureManager::~TextureManager()
{
}

Texture* TextureManager::CreateTextureFromFile(const wchar_t* file_path)
{
	return static_cast<Texture*>(CreateResourceFromFileConcerete(file_path));
}

Texture* TextureManager::CreateTextureFromFileAssets(const wchar_t* file_name)
{
	const wchar_t* file_path = L"Assets\\Textures\\";

	std::wstring a = file_path;
	std::wstring b = file_name;
	std::wstring c = a + b;

	return static_cast<Texture*>(CreateResourceFromFileConcerete(c.c_str()));;
}


Resource* TextureManager::CreateResourceFromFileConcerete(const wchar_t* file_path)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...) {}

	return tex;
}
