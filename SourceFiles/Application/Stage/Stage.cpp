#include "Stage.h"

void Stage::PlayerToEnemy()
{
	if (pPlayer->IsHide()) { return; }

	// �v���C���[�ƓG�̖ڐ������̂Ȃ��p�����߂�
	Vector2 toEyePlayer = *playerPos - WEConst(Vector2, "EnemyEyePos");
	float dot = Dot({ 0,1 }, Normalize(toEyePlayer));
	Angle theta = std::acos(dot);
	theta = std::abs(theta - *enemyEyeDir);

	// �Q�[���I�[�o�[
	if (theta <= Angle(4)) { WristerEngine::SceneManager::GetInstance()->ChangeScene(Scene::GameOver); }
}

void Stage::PlayerToGoal() {
	if (pPlayer->IsHide()) { return; }

	//�v���C���[�ƃS�[���̈ʒu�֌W���v�Z
	Vector2 hit = *goalPos - *playerPos;
	//�Q�[���N���A
	if (hit.x <= 0 && hit.y <= 0) {
		if (hit.x >= -WEConst(Vector2, "PlayerSize").x && hit.y >= -WEConst(Vector2, "PlayerSize").y) {
			WristerEngine::SceneManager::GetInstance()->ChangeScene(Scene::Clear);
		}
	}
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
			playerPos = pPlayer->GetPosition();
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
	for (auto& obj : stageObjects) { obj->Update(); }
}

void Stage::Draw()
{
	for (auto& obj : stageObjects) { obj->Draw(); }
}