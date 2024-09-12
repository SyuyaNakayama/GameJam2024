#pragma once
#include "JsonLoader.h"
#include "Vector.h"

struct ObjectData
{
	std::string name;
	float posX;
	Vector2 size;
	Vector2 e_eyePos;
	Vector2 e_gaugePos;
	int e_attackInterval;
	int e_attackTime;
	std::array<int, 2> e_angleRange{};
	bool e_flip;
};

class LevelLoader : public WristerEngine::JsonLoader
{
public:
	std::vector<ObjectData> LoadLevel(const std::string& fileName);
};