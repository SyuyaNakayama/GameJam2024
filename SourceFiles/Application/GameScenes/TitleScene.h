#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"

// UI�`��N���X(TitleScene�p)
class UIDrawerTitleScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
};

// �^�C�g���V�[��
class TitleScene : public WristerEngine::BaseScene
{
	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;

	OperateConfig* operate = OperateConfig::GetInstance();
};