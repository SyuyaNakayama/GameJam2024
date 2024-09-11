#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"

class Stage
{
	// �X�e�[�W��ɂ���Q�[���\����
	std::list<std::unique_ptr<WristerEngine::_2D::GameObject>> stageObjects;

	// �G������ł邩�̌��o�Ə���
	void EnemyDie();

public:
	~Stage() { stageObjects.clear(); }

	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
};