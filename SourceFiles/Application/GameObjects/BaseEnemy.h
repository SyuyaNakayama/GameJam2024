#pragma once
#include "GameObject.h"

class BaseEnemy : public WristerEngine::_2D::GameObject
{
	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
};