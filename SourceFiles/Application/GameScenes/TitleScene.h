#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "AudioManager.h"

// UI�`��N���X(TitleScene�p)
class UIDrawerTitleScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
};

// �^�C�g���V�[��
class TitleScene : public WristerEngine::BaseScene
{
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::Audio* audio_select;
	WristerEngine::Audio* bgm;

	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
	
	void Draw() override;

	OperateConfig* operate = OperateConfig::GetInstance();

	float chargeMove;
	bool isUDChange;

	//�^�C�g���p�X�v���C�g
	std::unique_ptr<WristerEngine::_2D::Sprite> bg;
	std::unique_ptr<WristerEngine::_2D::Sprite> player;
	std::unique_ptr<WristerEngine::_2D::Sprite> logo;
};