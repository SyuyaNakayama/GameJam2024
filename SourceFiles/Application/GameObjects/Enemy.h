#pragma once
#include "BaseEnemy.h"
#include "Collider.h"
#include "Easing.h"

class Enemy : public BaseEnemy
{
	std::unique_ptr<WristerEngine::_2D::Sprite> eyeBeam;
	WristerEngine::Easing beamRotEasing;
	std::unique_ptr<WristerEngine::_2D::Sprite> hpGauge;
	float hpRate = 1.0f;

	// BaseEnemy ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize(const ObjectData& objData) override;
	void Update() override;
	void Draw() override;
	void OnCollision(WristerEngine::_2D::ColliderGroup* collider) override;

public:
	const float* GetEyeAngle() const { return &eyeBeam->rotation; }
	bool IsDead() const { return hpRate <= 0; }
};