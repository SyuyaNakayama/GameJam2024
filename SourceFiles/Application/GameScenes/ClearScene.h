#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"

// UI�`��N���X(ClearScene�p)
class UIDrawerClearScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
};

// �N���A�V�[��
class ClearScene : public WristerEngine::BaseScene
{
	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
};