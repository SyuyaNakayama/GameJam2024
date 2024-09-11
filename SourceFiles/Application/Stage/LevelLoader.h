#pragma once
#include "JsonLoader.h"
#include "Vector.h"

struct ObjectData
{
	std::string name;
	float posX;
	Vector2 size;
};

class LevelLoader : public WristerEngine::JsonLoader
{
public:
	std::vector<ObjectData> LoadLevel(const std::string& fileName);
};