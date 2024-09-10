#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"
#include "Collider.h"

class Goal : public WristerEngine::_2D::GameObject, public WristerEngine::_2D::ColliderGroup
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;

	// GameObject ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() { sprite->Draw(); }

public:
	const Vector2* GetPosition() const { return &sprite->position; }
};