#pragma once
#include <string>

class SceneReader
{
public:
	SceneReader(std::string _directory);
	~SceneReader();

	void ReadFromFile();

private:
	std::string directory;
};