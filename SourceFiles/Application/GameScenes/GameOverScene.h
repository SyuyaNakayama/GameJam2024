#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"

class UIDrawerGameOverScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
};

class GameOverScene : public WristerEngine::BaseScene
{
	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
};