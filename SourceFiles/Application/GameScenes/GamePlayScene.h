#pragma once
#include "BaseScene.h"
#include "AbstractUIDrawer.h"

class UIDrawerGamePlayScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
};

class GamePlayScene : public WristerEngine::BaseScene
{
	// BaseScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
};