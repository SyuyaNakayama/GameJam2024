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
	bool isGoal = false;

	//UI
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_attack;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_dive;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_coolTime1;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_coolTime2;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_key_space;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_key_down;

	// �Ȃ�炩�̃A�N�V����
	void (Player::* Action)() = nullptr;
	void Hide(); // �B���
	void Attack(); // �U��
	// �N�[���^�C��
	WristerEngine::FrameTimer hideCoolTimer;
	WristerEngine::FrameTimer attackCoolTimer;

	bool isCanUseHide = true, isCanUseAttack = true;

	//�A�j���[�V�����ϐ�
	int animTime;
	//�N�[���^�C��
	float coolCutPosA;
	float coolCutPosH;
	int countCoolTimeA;
	int countCoolTimeH;
	bool coolTimeCountStartA;
	bool coolTimeCountStartH;
	//�U������
	float attackCutPos;

	void Move(); // �ړ�
	void UITimer();	//UI�ł̃N�[���^�C�����o��
	void Animations();	//�v���C���[�̃A�j���[�V��������
	void InitializeUI();//�����Ȃ肻���Ȃ̂�UI�����̏����������ʌp��

	// GameObject ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw();
	void OnCollision(WristerEngine::_2D::ColliderGroup* group) override;
public:
	bool IsHide() const { return Action == &Player::Hide; }
	const WristerEngine::_2D::Sprite* GetSprite() const { return sprite.get(); }
	bool IsGoal() const { return isGoal; }
};