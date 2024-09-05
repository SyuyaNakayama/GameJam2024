#pragma once
#include "Player.h"
#include "Enemy.h"

class Stage
{
	// ステージ上にあるゲーム表示物
	std::list<std::unique_ptr<WristerEngine::_2D::GameObject>> stageObjects;

	const Player* pPlayer = nullptr;
	const Vector2* playerPos = nullptr;
	const float* enemyEyeDir = nullptr;

	// プレイヤーと敵の変数のやり取り
	void PlayerToEnemy();

public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
};