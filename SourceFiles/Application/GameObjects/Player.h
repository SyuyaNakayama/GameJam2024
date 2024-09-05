#pragma once
#include "GameObject.h"
#include "Sprite.h"

class Player : public WristerEngine::_2D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> playerSprite;

	// GameObject ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() { playerSprite->Draw(); }
};