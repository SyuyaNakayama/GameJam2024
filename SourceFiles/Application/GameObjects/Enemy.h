#pragma once
#include "BaseEnemy.h"
#include "Collider.h"
#include "Easing.h"
#include "Random.h"
#include "AudioManager.h"

class Enemy : public BaseEnemy
{
	std::unique_ptr<WristerEngine::_2D::Sprite> eyeBeam;
	WristerEngine::Easing beamRotEasing;
	std::array<int, 2> beamAngleRange;
	WristerEngine::Audio* audio_eyeMove = nullptr;
	bool isPreEyeMove = false, isEyeMove = false;
	float eyePreRot = 0;

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
	std::unique_ptr<WristerEngine::_2D::Sprite> whiteBody;
	WristerEngine::FrameTimer attackInterval;
	WristerEngine::FrameTimer attackTimer;
	WristerEngine::LoopEasing whiteAlphaEasing;

	// BaseEnemy ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize(const ObjectData& objData) override;
	void Update() override;
	void Draw() override;
};