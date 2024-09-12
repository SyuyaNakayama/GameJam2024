#pragma once
#include "MyGameObject.h"

class BaseEnemy : public MyGameObject
{
protected:
	std::unique_ptr<WristerEngine::_2D::Sprite> hpGauge;
	float hpRate = 1.0f;

	virtual void Initialize(const ObjectData& objData) override;
	virtual void Update() override;
	virtual void Draw() override;
	void OnCollision(WristerEngine::_2D::ColliderGroup* collider) override;
	
public:
	bool IsDead() const { return hpRate <= 0; }
};