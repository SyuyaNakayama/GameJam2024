#pragma once
#include "BaseEnemy.h"
#include "Collider.h"

class Enemy : public BaseEnemy, public WristerEngine::_2D::ColliderGroup
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	std::unique_ptr<WristerEngine::_2D::Sprite> eyeBeam;

	// BaseEnemy ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() override { sprite->Draw(); eyeBeam->Draw(); }
	void OnCollision(WristerEngine::_2D::ColliderGroup* collider) override;

public:
	const float* GetEyeAngle() const { return &eyeBeam->rotation; }
};