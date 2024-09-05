#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"

class Player : public WristerEngine::_2D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::FrameTimer hideTimer; // ‰B‚ê‚Ä‚¢‚éŽžŠÔ

	// ‚È‚ñ‚ç‚©‚ÌƒAƒNƒVƒ‡ƒ“
	void (Player::* Action)() = nullptr;

	void Move(); // ˆÚ“®
	void Hide(); // ‰B‚ê‚é

	// GameObject ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() { sprite->Draw(); }

public:
	const Vector2* GetPosition() const { return &sprite->position; }
	bool IsHide() const { return Action == &Player::Hide; }
};