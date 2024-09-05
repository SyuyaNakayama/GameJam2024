#pragma once
#include "Player.h"
#include "Enemy.h"

class Stage
{
	// �X�e�[�W��ɂ���Q�[���\����
	std::list<std::unique_ptr<WristerEngine::_2D::GameObject>> stageObjects;

	const Player* pPlayer = nullptr;
	const Vector2* playerPos = nullptr;
	const float* enemyEyeDir = nullptr;

	// �v���C���[�ƓG�̕ϐ��̂����
	void PlayerToEnemy();

public:
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
};