#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"
#include "Collider.h"

class Player : public WristerEngine::_2D::GameObject, public WristerEngine::_2D::ColliderGroup
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	std::unique_ptr<WristerEngine::_2D::Sprite> sprites;
	std::unique_ptr<WristerEngine::_2D::Sprite> attackArea;
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::FrameTimer hideTimer; // 隠れている時間
	WristerEngine::FrameTimer attackTimer; // 攻撃している時間

	//UI
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_attack;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_dive;

	// なんらかのアクション
	void (Player::* Action)() = nullptr;
	void Hide(); // 隠れる
	void Attack(); // 攻撃
	// クールタイム
	WristerEngine::FrameTimer hideCoolTimer;
	WristerEngine::FrameTimer attackCoolTimer;

	bool isCanUseHide = true, isCanUseAttack = true;

	void Move(); // 移動

	// GameObject を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() { sprites->Draw(); sprite->Draw(); attackArea->Draw(); }
	void OnCollision(WristerEngine::_2D::ColliderGroup* group) override;

public:
	bool IsHide() const { return Action == &Player::Hide; }
	const WristerEngine::_2D::Sprite* GetSprite() const { return sprite.get(); }
};