#pragma once
#include "BaseEnemy.h"

class Enemy : public BaseEnemy
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	std::unique_ptr<WristerEngine::_2D::Sprite> eyeBeam;

	// BaseEnemy を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override { sprite->Draw(); eyeBeam->Draw(); }

public:
	const float* GetEyeAngle() const { return &eyeBeam->rotation; }
};