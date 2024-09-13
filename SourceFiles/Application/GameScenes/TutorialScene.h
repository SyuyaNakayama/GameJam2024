#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "Stage.h"
#include "AudioManager.h"
#include "AudioManager.h"

class UIDrawerTutorialScene : public WristerEngine::_2D::AbstractUIDrawer
{

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
};

class TutorialScene : public WristerEngine::BaseScene
{
	// �X�e�[�W�I�u�W�F�N�g
	Stage stage;
	std::unique_ptr<WristerEngine::_2D::Sprite> background; // �w�i
	WristerEngine::Audio* bgm;

public:

	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

