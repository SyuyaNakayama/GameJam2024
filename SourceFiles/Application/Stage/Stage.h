#pragma once
#include "Player.h"
#include "BaseEnemy.h"

class Stage
{
	// �X�e�[�W��ɂ���Q�[���\����
	std::list<std::unique_ptr<WristerEngine::_2D::GameObject>> stageObjects;

public:
	// ������
	void Initialize();
	// �X�V
	void Update() { for (auto& obj : stageObjects) { obj->Update(); } }
	// �`��
	void Draw();
};