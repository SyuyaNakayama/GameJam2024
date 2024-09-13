#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "AudioManager.h"

// UI�`��N���X(GameOverScene�p)
class UIDrawerGameOverScene : public WristerEngine::_2D::AbstractUIDrawer
{
	int animTime = 0;
	int maxAnimTime = 0;

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
};

// �Q�[���I�[�o�[�V�[��
class GameOverScene : public WristerEngine::BaseScene
{
	OperateConfig* operate = OperateConfig::GetInstance();
	WristerEngine::Audio* audio_select = nullptr;
	WristerEngine::Audio* bgm = nullptr;

	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
};