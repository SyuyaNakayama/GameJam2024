#include "LevelLoader.h"

std::vector<ObjectData> LevelLoader::LoadLevel(const std::string& fileName)
{
	std::vector<ObjectData> objects;
	auto loaded = LoadJson(fileName);
	for (nlohmann::json& object : loaded["objects"])
	{
		ObjectData obj;
		obj.name = object["name"];
		obj.posX = object["positionX"];
		obj.size.x = object["size"][0];
		obj.size.y = object["size"][1];
		objects.push_back(obj);
	}
	return objects;
}
