#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"


class Player : public WristerEngine::_2D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	OperateConfig* operate = OperateConfig::GetInstance();
	bool isHide = false; // 隠れているか
	WristerEngine::FrameTimer hideTimer; // 隠れている時間

	// なんらかのアクション
	void (Player::*Action)() = nullptr;

	void Move(); // 移動
	void Hide(); // 隠れる

	// GameObject を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() { sprite->Draw(); }
};