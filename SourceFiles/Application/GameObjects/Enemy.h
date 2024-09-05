#pragma once
#include "BaseEnemy.h"

class Enemy : public BaseEnemy
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;

	// BaseEnemy ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override { sprite->Draw(); }
};