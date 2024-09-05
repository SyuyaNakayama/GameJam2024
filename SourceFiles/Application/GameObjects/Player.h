#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"


class Player : public WristerEngine::_2D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	OperateConfig* operate = OperateConfig::GetInstance();
	bool isHide = false; // ‰B‚ê‚Ä‚¢‚é‚©
	WristerEngine::FrameTimer hideTimer; // ‰B‚ê‚Ä‚¢‚éŽžŠÔ

	// ‚È‚ñ‚ç‚©‚ÌƒAƒNƒVƒ‡ƒ“
	void (Player::*Action)() = nullptr;

	void Move(); // ˆÚ“®
	void Hide(); // ‰B‚ê‚é

	// GameObject ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() { sprite->Draw(); }
};