#pragma once

#include <string>

class SceneWriter
{
public:
	SceneWriter(std::string _directory);
	~SceneWriter();

	void WriteToFile();

private:
	std::string directory;
};

