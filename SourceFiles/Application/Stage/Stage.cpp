#include "Stage.h"
#include "ShareValue.h"
#include <imgui.h>
#include "ImGuiManager.h"

using namespace WristerEngine::_2D;

void Stage::EnemyDie()
{
	stageObjects.remove_if([](const std::unique_ptr<WristerEngine::_2D::GameObject>& obj)
		{
			if (dynamic_cast<BaseEnemy*>(obj.get()) == nullptr) { return false; }
			const BaseEnemy* pEnemy = dynamic_cast<BaseEnemy*>(obj.get());
			return pEnemy->IsDead();
		});
}

void Stage::Initialize()
{
	std::vector<ObjectData> objects = levelLoader.LoadLevel("stage1");

	for (auto obj : objects)
	{
		std::unique_ptr<GameObject> stageObject;

		if (obj.name == "Player") { stageObject = std::make_unique<Player>(); }
		else if (obj.name == "Enemy") { stageObject = std::make_unique<Enemy>(); }
		else if (obj.name == "DarumaEnemy") { stageObject = std::make_unique<DarumaEnemy>(); }
		else if (obj.name == "Goal") { stageObject = std::make_unique<Goal>(); }
		assert(stageObject);

		// オブジェクトの登録
		stageObject->Initialize(obj);
		stageObjects.push_back(std::move(stageObject));
	}
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