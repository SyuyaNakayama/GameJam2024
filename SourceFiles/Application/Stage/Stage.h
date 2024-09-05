#pragma once
#include "Player.h"
#include "BaseEnemy.h"

class Stage
{
	// ステージ上にあるゲーム表示物
	std::list<std::unique_ptr<WristerEngine::_2D::GameObject>> stageObjects;

public:
	// 初期化
	void Initialize();
	// 更新
	void Update() { for (auto& obj : stageObjects) { obj->Update(); } }
	// 描画
	void Draw();
};