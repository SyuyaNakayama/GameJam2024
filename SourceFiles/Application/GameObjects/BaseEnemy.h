#pragma once
#include "GameObject.h"

class BaseEnemy : public WristerEngine::_2D::GameObject
{
	// GameObject を介して継承されました
	void Initialize() override;
	void Update() override;
};