#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"
#include "Stage.h"

class UIDrawerTutorialScene : public WristerEngine::_2D::AbstractUIDrawer
{

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
};

class TutorialScene : public WristerEngine::BaseScene
{
	// �X�e�[�W�I�u�W�F�N�g
	Stage stage;

public:

	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

