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
	WristerEngine::FrameTimer hideTimer; // �B��Ă��鎞��
	WristerEngine::FrameTimer attackTimer; // �U�����Ă��鎞��

	// �Ȃ�炩�̃A�N�V����
	void (Player::* Action)() = nullptr;
	void Hide(); // �B���
	void Attack(); // �U��
	// �N�[���^�C��
	WristerEngine::FrameTimer hideCoolTimer;
	WristerEngine::FrameTimer attackCoolTimer;

	bool isCanUseHide = true, isCanUseAttack = true;

	void Move(); // �ړ�

	// GameObject ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() { sprite->Draw(); attackArea->Draw(); }
	void OnCollision(WristerEngine::_2D::ColliderGroup* group) override;

public:
	bool IsHide() const { return Action == &Player::Hide; }
	const WristerEngine::_2D::Sprite* GetSprite() const { return sprite.get(); }
};