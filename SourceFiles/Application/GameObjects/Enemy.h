#pragma once
#include "BaseEnemy.h"
#include "Collider.h"
#include "Easing.h"
#include "Random.h"

class Enemy : public BaseEnemy
{
	std::unique_ptr<WristerEngine::_2D::Sprite> eyeBeam;
	WristerEngine::Easing beamRotEasing;

	// BaseEnemy ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize(const ObjectData& objData) override;
	void Update() override;
	void Draw() override;

public:
	const float* GetEyeAngle() const { return &eyeBeam->rotation; }
};

class DarumaEnemy : public BaseEnemy
{
	std::unique_ptr<WristerEngine::_2D::Sprite> attack;
	WristerEngine::FrameTimer attackInterval;
	WristerEngine::FrameTimer attackTimer;
	WristerEngine::Random_Float shakeBody; // —\”õ“®ì

	// BaseEnemy ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize(const ObjectData& objData) override;
	void Update() override;
	void Draw() override;
};