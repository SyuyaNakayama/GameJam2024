#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"

class Player : public WristerEngine::_2D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	OperateConfig* operate = OperateConfig::GetInstance();

	void Move();

	// GameObject ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() { sprite->Draw(); }
};