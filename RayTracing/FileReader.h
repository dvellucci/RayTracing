#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"

#define ASPECT_EPSILON 0.01

class FileReader
{
public:
	FileReader(std::string filePath);
	~FileReader();

	std::shared_ptr<Scene> setObjectData();

	std::vector<std::string>& getLinesVector() { return m_fileInputLines; }


private:
	std::vector<std::string> m_fileInputLines;
};