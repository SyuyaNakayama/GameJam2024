#pragma once
#include "MyGameObject.h"
#include "OperateConfig.h"
#include "Collider.h"

class Goal : public MyGameObject
{
	// GameObject を介して継承されました
	void Initialize(const ObjectData& objData) override;
	void Update() override;
	void Draw() { sprite->Draw(); }

public:
	const Vector2* GetPosition() const { return &sprite->position; }
};