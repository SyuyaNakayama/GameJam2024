#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"

class Player : public WristerEngine::_2D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	std::unique_ptr<WristerEngine::_2D::Sprite> attackArea;
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::FrameTimer hideTimer; // ‰B‚ê‚Ä‚¢‚éŽžŠÔ
	WristerEngine::FrameTimer attackTimer; // ‰B‚ê‚Ä‚¢‚éŽžŠÔ

	// ‚È‚ñ‚ç‚©‚ÌƒAƒNƒVƒ‡ƒ“
	void (Player::* Action)() = nullptr;
	void Hide(); // ‰B‚ê‚é
	void Attack(); // UŒ‚

	void Move(); // ˆÚ“®

	// GameObject ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() { sprite->Draw(); attackArea->Draw(); }

public:
	bool IsHide() const { return Action == &Player::Hide; }
	const WristerEngine::_2D::Sprite* GetSprite() const { return sprite.get(); }
};