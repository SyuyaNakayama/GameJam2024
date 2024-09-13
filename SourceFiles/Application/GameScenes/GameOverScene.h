#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "AudioManager.h"

// UI�`��N���X(GameOverScene�p)
class UIDrawerGameOverScene : public WristerEngine::_2D::AbstractUIDrawer
{
	int animTime;
	int maxAnimTime;

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
};

// �Q�[���I�[�o�[�V�[��
class GameOverScene : public WristerEngine::BaseScene
{
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::Audio* audio_select;
	WristerEngine::Audio* bgm;

	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
};