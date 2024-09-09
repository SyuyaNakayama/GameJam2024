#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"

class Stage
{
	// �X�e�[�W��ɂ���Q�[���\����
	std::list<std::unique_ptr<WristerEngine::_2D::GameObject>> stageObjects;

	const Player* pPlayer = nullptr;
	const Vector2* goalPos = nullptr;
	const float* enemyEyeDir = nullptr;
	std::unique_ptr<WristerEngine::_2D::Sprite> debugSprite;
	std::unique_ptr<WristerEngine::_2D::Sprite> debugSprite2;

	// �v���C���[�ƓG�̕ϐ��̂����
	void PlayerToEnemy();
	// �v���C���[�ƃS�[���̕ϐ��̂����
	void PlayerToGoal();
	// �G������ł邩�̌��o�Ə���
	void EnemyDie();

public:
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
};