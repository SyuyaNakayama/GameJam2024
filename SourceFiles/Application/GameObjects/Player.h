#pragma once
#include "GameObject.h"
#include "Sprite.h"

class Player : public WristerEngine::_3D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> playerSprite;

	// GameObject ����Čp������܂���
	void Initialize(const ObjectData& objectData) override;
	void Update() override;
};