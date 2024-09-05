#pragma once
#include "GameObject.h"
#include "Sprite.h"

class Player : public WristerEngine::_3D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> playerSprite;

	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize(const ObjectData& objectData) override;
	void Update() override;
};