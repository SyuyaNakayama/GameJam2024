#include "Stage.h"

void Stage::Initialize()
{
	stageObjects.push_back(std::make_unique<Player>());
	stageObjects.push_back(std::make_unique<Enemy>());
	for (auto& obj : stageObjects) { obj->Initialize(); }
}

void Stage::Draw()
{
	for (auto& obj : stageObjects) { obj->Draw(); }
}