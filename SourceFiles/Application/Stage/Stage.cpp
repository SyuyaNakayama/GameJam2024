#include "Stage.h"
#include "ShareValue.h"
#include <imgui.h>
#include "ImGuiManager.h"

using namespace WristerEngine::_2D;

void Stage::EnemyDie()
{
	stageObjects.remove_if([](const std::unique_ptr<WristerEngine::_2D::GameObject>& obj)
		{
			if (dynamic_cast<Enemy*>(obj.get()) == nullptr) { return false; }
			const Enemy* pEnemy = dynamic_cast<Enemy*>(obj.get());
			return pEnemy->IsDead();
		});
}

void Stage::Initialize()
{
	// オブジェクトの登録
	stageObjects.push_back(std::make_unique<Player>());
	stageObjects.push_back(std::make_unique<Enemy>());
	stageObjects.push_back(std::make_unique<Goal>());
	for (auto& obj : stageObjects) { obj->Initialize(); }
}

void Stage::Update()
{
	EnemyDie();
	for (auto& obj : stageObjects) { obj->Update(); }
}

void Stage::Draw()
{
	for (auto& obj : stageObjects) { obj->Draw(); }
}