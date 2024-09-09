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
	std::unique_ptr<WristerEngine::_2D::Sprite> hide;	//�����Ă��鎞�̃X�v���C�g
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::FrameTimer hideTimer; // �B��Ă��鎞��
	WristerEngine::FrameTimer attackTimer; // �U�����Ă��鎞��

	//UI
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_attack;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_dive;

	// �Ȃ�炩�̃A�N�V����
	void (Player::* Action)() = nullptr;
	void Hide(); // �B���
	void Attack(); // �U��
	// �N�[���^�C��
	WristerEngine::FrameTimer hideCoolTimer;
	WristerEngine::FrameTimer attackCoolTimer;

	bool isCanUseHide = true, isCanUseAttack = true;

	int animTime;

	void Move(); // �ړ�

	void UITimer();	//UI�ł̃N�[���^�C�����o��

	void Animations();	//�v���C���[�̃A�j���[�V��������

	// GameObject ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() { sprites->Draw(); sprite->Draw(); attackArea->Draw(); hide->Draw();  ui_attack->Draw(); ui_dive->Draw(); }
	void OnCollision(WristerEngine::_2D::ColliderGroup* group) override;
public:
	bool IsHide() const { return Action == &Player::Hide; }
	const WristerEngine::_2D::Sprite* GetSprite() const { return sprite.get(); }
};