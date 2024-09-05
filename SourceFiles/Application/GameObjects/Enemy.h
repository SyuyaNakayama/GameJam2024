#pragma once
#include "BaseEnemy.h"

class Enemy : public BaseEnemy
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	std::unique_ptr<WristerEngine::_2D::Sprite> eyeBeam;

	// BaseEnemy ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override { sprite->Draw(); eyeBeam->Draw(); }
};