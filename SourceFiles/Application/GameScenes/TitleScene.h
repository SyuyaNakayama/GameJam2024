#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"

class UIDrawerTitleScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
};

class TitleScene : public WristerEngine::BaseScene
{
	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
};