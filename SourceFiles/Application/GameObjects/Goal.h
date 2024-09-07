#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "OperateConfig.h"

class Goal : public WristerEngine::_2D::GameObject
{
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;

	// GameObject ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() { sprite->Draw(); }

public:
	const Vector2* GetPosition() const { return &sprite->position; }
};