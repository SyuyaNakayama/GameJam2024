#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"

class Stage
{
	// ステージ上にあるゲーム表示物
	std::list<std::unique_ptr<WristerEngine::_2D::GameObject>> stageObjects;

	const Player* pPlayer = nullptr;
	const Vector2* goalPos = nullptr;
	const float* enemyEyeDir = nullptr;
	std::unique_ptr<WristerEngine::_2D::Sprite> debugSprite;
	std::unique_ptr<WristerEngine::_2D::Sprite> debugSprite2;

	// プレイヤーと敵の変数のやり取り
	void PlayerToEnemy();
	// プレイヤーとゴールの変数のやり取り
	void PlayerToGoal();
	// 敵が死んでるかの検出と消滅
	void EnemyDie();

public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
};