#pragma once
#include "GameObject.h"

class BaseEnemy : public WristerEngine::_2D::GameObject
{
	// GameObject ����Čp������܂���
	void Initialize() override;
	void Update() override;
};