#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"

class UIDrawerGamePlayScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
};

class GamePlayScene : public WristerEngine::BaseScene
{
	// BaseScene ����Čp������܂���
	void Initialize() override;
	void Update() override;
};