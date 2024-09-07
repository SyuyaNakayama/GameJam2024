#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"

class Stage
{
	// �X�e�[�W��ɂ���Q�[���\����
	std::list<std::unique_ptr<WristerEngine::_2D::GameObject>> stageObjects;

	const Player* pPlayer = nullptr;
	const Vector2* playerPos = nullptr;
	const Vector2* goalPos = nullptr;
	const float* enemyEyeDir = nullptr;

	// �v���C���[�ƓG�̕ϐ��̂����
	void PlayerToEnemy();
	// �v���C���[�ƃS�[���̕ϐ�������
	void PlayerToGoal();

public:
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
};