#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"

class Stage
{
	// ステージ上にあるゲーム表示物
	std::list<std::unique_ptr<WristerEngine::_2D::GameObject>> stageObjects;

	// 敵が死んでるかの検出と消滅
	void EnemyDie();

public:
	~Stage() { stageObjects.clear(); }

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
};