#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"
#include "LevelLoader.h"
#include "AudioManager.h"

class Stage
{
	// �X�e�[�W��ɂ���Q�[���\����
	std::list<std::unique_ptr<WristerEngine::_2D::GameObject>> stageObjects;

	LevelLoader levelLoader;
	WristerEngine::Audio* audio_enemyDeath = nullptr;

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