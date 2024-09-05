#pragma once
#include "GameObject.h"
#include "Sprite.h"

class Player : public WristerEngine::_3D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> playerSprite;

	// GameObject を介して継承されました
	void Initialize(const ObjectData& objectData) override;
	void Update() override;
};