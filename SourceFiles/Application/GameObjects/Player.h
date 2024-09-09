#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"
#include "Collider.h"

class Player : public WristerEngine::_2D::GameObject, public WristerEngine::_2D::ColliderGroup
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	std::unique_ptr<WristerEngine::_2D::Sprite> attackArea;
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::FrameTimer hideTimer; // ‰B‚ê‚Ä‚¢‚éŽžŠÔ
	WristerEngine::FrameTimer attackTimer; // UŒ‚‚µ‚Ä‚¢‚éŽžŠÔ

	// ‚È‚ñ‚ç‚©‚ÌƒAƒNƒVƒ‡ƒ“
	void (Player::* Action)() = nullptr;
	void Hide(); // ‰B‚ê‚é
	void Attack(); // UŒ‚
	// ƒN[ƒ‹ƒ^ƒCƒ€
	WristerEngine::FrameTimer hideCoolTimer;
	WristerEngine::FrameTimer attackCoolTimer;

	bool isCanUseHide = true, isCanUseAttack = true;

	void Move(); // ˆÚ“®

	// GameObject ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() { sprite->Draw(); attackArea->Draw(); }
	void OnCollision(WristerEngine::_2D::ColliderGroup* group) override;

public:
	bool IsHide() const { return Action == &Player::Hide; }
	const WristerEngine::_2D::Sprite* GetSprite() const { return sprite.get(); }
};