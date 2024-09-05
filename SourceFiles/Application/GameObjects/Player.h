#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"

class Player : public WristerEngine::_2D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::FrameTimer hideTimer; // �B��Ă��鎞��

	// �Ȃ�炩�̃A�N�V����
	void (Player::* Action)() = nullptr;

	void Move(); // �ړ�
	void Hide(); // �B���

	// GameObject ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() { sprite->Draw(); }

public:
	const Vector2* GetPosition() const { return &sprite->position; }
	bool IsHide() const { return Action == &Player::Hide; }
};