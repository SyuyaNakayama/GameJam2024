#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "AudioManager.h"

// UI�`��N���X(ClearScene�p)
class UIDrawerClearScene : public WristerEngine::_2D::AbstractUIDrawer
{
	int animTime = 0;
	int maxAnimTime = 0;

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
};

// �N���A�V�[��
class ClearScene : public WristerEngine::BaseScene
{
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::Audio* audio_select;
	WristerEngine::Audio* bgm;

	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
};