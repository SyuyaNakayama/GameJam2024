#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"

class UIDrawerClearScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
};

class ClearScene : public WristerEngine::BaseScene
{
	// BaseScene を介して継承されました
	void Initialize() override;
	void Update() override;
};