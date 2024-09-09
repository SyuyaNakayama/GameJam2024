#include "Stage.h"
#include <imgui.h>

using namespace WristerEngine::_2D;

void Stage::PlayerToEnemy()
{
	if (pPlayer->IsHide()) { return; }

	// �v���C���[�ƓG�̖ڐ������̂Ȃ��p�Ƃ����߂�
	Vector2 toEyePlayer = pPlayer->GetSprite()->position - WEConst(Vector2, "EnemyEyePos");
	float dot = Dot({ 0,1 }, Normalize(toEyePlayer));
	Angle theta = std::acos(dot);
	theta = std::abs(theta - *enemyEyeDir);

	// �Q�[���I�[�o�[
	//if (theta <= Angle(4)) { WristerEngine::SceneManager::GetInstance()->ChangeScene(Scene::GameOver); }

	// ��ŏC��
	// �v���C���[�̍���[�ƉE���[�̍��W�����߂�
	//const Sprite* pSprite = pPlayer->GetSprite();
	//Vector2 pPosLT, pPosRB;
	//pPosLT = pPosRB = pSprite->position;
	//pPosLT -= Vector2(pSprite->size.x * pSprite->anchorPoint.x, pSprite->size.y * pSprite->anchorPoint.y);
	//pPosRB += Vector2(pSprite->size.x * (1.0f - pSprite->anchorPoint.x), pSprite->size.y * (1.0f - pSprite->anchorPoint.y));

	//debugSprite = Sprite::Create("white1x1.png", WEConst(Vector2, "EnemyEyePos"));
	//debugSprite->size.x = 1000;
	//debugSprite->rotation = Angle(90 + 4) + *enemyEyeDir;
	//debugSprite->Update();

	//Vector2 vec = Normalize(Vector2(std::cos(debugSprite->rotation), std::sin(debugSprite->rotation)));
	//debugSprite2 = Sprite::Create("white1x1.png", WEConst(Vector2, "EnemyEyePos"));
	//debugSprite2->size *= 10;
	//debugSprite2->position = WEConst(Vector2, "EnemyEyePos") + vec * 300;
	//debugSprite2->Update();

	//Vector2 toEyePlayerRB = pPosRB - WEConst(Vector2, "EnemyEyePos");
	//float crossRB = Dot(vec, Normalize(toEyePlayerRB));
	//if (crossRB <= 0) { ImGui::Text("Hit!(RB)"); }
}

void Stage::PlayerToGoal() {
	if (pPlayer->IsHide()) { return; }

	//�v���C���[�ƃS�[���̈ʒu�֌W���v�Z
	Vector2 hit = *goalPos - pPlayer->GetSprite()->position;
	//�Q�[���N���A
	if (hit.x < WEConst(Vector2, "PlayerSize").x / 2 && hit.y <= WEConst(Vector2, "PlayerSize").y / 2) {
		if (hit.x > -WEConst(Vector2, "PlayerSize").x / 2 && hit.y >= -WEConst(Vector2, "PlayerSize").y / 2) {
			WristerEngine::SceneManager::GetInstance()->ChangeScene(Scene::Clear);
		}
	}
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
	// �I�u�W�F�N�g�̓o�^
	stageObjects.push_back(std::make_unique<Player>());
	stageObjects.push_back(std::make_unique<Enemy>());
	stageObjects.push_back(std::make_unique<Goal>());
	for (auto& obj : stageObjects) { obj->Initialize(); }

	// �v���C���[�ƓG�̏����擾
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
	//debugSprite->Draw();
	//debugSprite2->Draw();
}