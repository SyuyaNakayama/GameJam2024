#pragma once
#include "MyGameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"
#include "Collider.h"
#include "Random.h"
#include "Audio.h"

class Player : public MyGameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> attack;
	std::unique_ptr<WristerEngine::_2D::Sprite> dive;	//�����Ă��鎞�̃X�v���C�g
	std::unique_ptr<WristerEngine::_2D::Sprite> walk;	//�����Ă鎞
	std::unique_ptr<WristerEngine::_2D::Sprite> isAttack;	//�U����
	std::unique_ptr<WristerEngine::_2D::Sprite> drill;	//�U�����̃h����
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::FrameTimer diveTimer; // �����Ă��鎞��
	WristerEngine::FrameTimer attackTimer; // �U�����Ă��鎞��
	bool isGoal = false;

	//UI
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_attack;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_dive;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_coolTime1;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_coolTime2;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_key_space;
	std::unique_ptr<WristerEngine::_2D::Sprite> ui_key_down;
	std::unique_ptr<WristerEngine::_2D::Sprite> textBox;

	// �Ȃ�炩�̃A�N�V����
	void (Player::* Action)() = nullptr;
	void Dive(); // ����
	void Attack(); // �U��
	// �N�[���^�C��
	WristerEngine::FrameTimer diveCoolTimer;
	WristerEngine::FrameTimer attackCoolTimer;

	bool isCanUseDive = true, isCanUseAttack = true;

	//�A�j���[�V�����ϐ�
	int animTime;
	//�N�[���^�C��
	float coolCutPosA;
	float coolCutPosH;
	int countCoolTimeA;
	int countCoolTimeH;
	bool coolTimeCountStartA;
	bool coolTimeCountStartH;

	//�`���[�g���A���̐������I��������ǂ���
	bool isExplanation;
	float page;

	WristerEngine::Random_Float shakeBody;

	// ��
	WristerEngine::Audio* audio_attack;
	WristerEngine::Audio* audio_dive;

	void Move(); // �ړ�
	void UITimer();	//UI�ł̃N�[���^�C�����o��
	void InitializeUI();//�����Ȃ肻���Ȃ̂�UI�����̏����������ʌp��
	void Tutorial();	//�`���[�g���A������

	// GameObject ����Čp������܂���
	void Initialize(const ObjectData& objData) override;
	void Update() override;
	void Draw();
	void OnCollision(WristerEngine::_2D::ColliderGroup* group) override;
public:
	bool IsDive() const { return Action == &Player::Dive; }
	const WristerEngine::_2D::Sprite* GetSprite() const { return sprite.get(); }
	bool IsGoal() const { return isGoal; }
};