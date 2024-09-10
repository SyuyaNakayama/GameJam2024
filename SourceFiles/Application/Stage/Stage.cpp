#include "Stage.h"
#include <imgui.h>

using namespace WristerEngine::_2D;

void Stage::PlayerToEnemy()
{
	if (pPlayer->IsHide()) { return; }

	// 敵視野角を計算
	float leftRot = Angle(90 + WEConst(int,"EnemyEyeFOV")) + *enemyEyeDir;
	float rightRot = Angle(90 - WEConst(int, "EnemyEyeFOV")) + *enemyEyeDir;
	
	// プレイヤーの左上端と右下端の座標を求める
	const Sprite* pSprite = pPlayer->GetSprite();
	Vector2 pPosLT, pPosRB;
	pPosLT = pPosRB = pSprite->position;
	pPosLT -= Vector2(pSprite->size.x * pSprite->anchorPoint.x, pSprite->size.y * pSprite->anchorPoint.y);
	pPosRB += Vector2(pSprite->size.x * (1.0f - pSprite->anchorPoint.x), pSprite->size.y * (1.0f - pSprite->anchorPoint.y));

	// 左上の接触判定
	Vector2 vec = Normalize(Vector2(std::cos(rightRot), std::sin(rightRot)));
	Vector2 toEyePlayerLT = Normalize(pPosLT - WEConst(Vector2, "EnemyEyePos"));
	float crossLT = Cross(vec, Normalize(toEyePlayerLT));

	// 右下の接触判定
	vec = Normalize(Vector2(std::cos(leftRot), std::sin(leftRot)));
	Vector2 toEyePlayerRB = Normalize(pPosRB - WEConst(Vector2, "EnemyEyePos"));
	float crossRB = Cross(vec, Normalize(toEyePlayerRB));
	
	// ゲームオーバー
	if (crossRB <= 0&& crossLT >= 0) { WristerEngine::SceneManager::GetInstance()->ChangeScene(Scene::GameOver); }
}

void Stage::PlayerToGoal() {
	if (pPlayer->IsHide()) { return; }

	//プレイヤーとゴールの位置関係を計算
	//Vector2 hit = *goalPos - pPlayer->GetSprite()->position;
	////ゲームクリア
	//if (hit.x < WEConst(Vector2, "PlayerSize").x / 2 && hit.y <= WEConst(Vector2, "PlayerSize").y / 2) {
	//	if (hit.x > -WEConst(Vector2, "PlayerSize").x / 2 && hit.y >= -WEConst(Vector2, "PlayerSize").y / 2) {
	//		WristerEngine::SceneManager::GetInstance()->ChangeScene(Scene::Clear);
	//	}
	//}
}

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

	// プレイヤーと敵の情報を取得
	for (auto& obj : stageObjects)
	{
		if (dynamic_cast<Player*>(obj.get()))
		{
			pPlayer = dynamic_cast<Player*>(obj.get());
		}
		else if (dynamic_cast<Enemy*>(obj.get()))
		{
			const Enemy* pEnemy = dynamic_cast<Enemy*>(obj.get());
			enemyEyeDir = pEnemy->GetEyeAngle();
		}
		else if (dynamic_cast<Goal*>(obj.get()))
		{
			const Goal* pGoal = dynamic_cast<Goal*>(obj.get());
			goalPos = pGoal->GetPosition();
		}
	}
}

void Stage::Update()
{
	PlayerToEnemy();
	PlayerToGoal();
	EnemyDie();
	for (auto& obj : stageObjects) { obj->Update(); }
}

void Stage::Draw()
{
	for (auto& obj : stageObjects) { obj->Draw(); }
}