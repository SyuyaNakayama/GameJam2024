#pragma once
#include "BaseEnemy.h"

class Enemy : public BaseEnemy
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;

	// BaseEnemy を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override { sprite->Draw(); }
};