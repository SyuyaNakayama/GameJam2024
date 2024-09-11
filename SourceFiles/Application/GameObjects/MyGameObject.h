#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"

class MyGameObject : public WristerEngine::_2D::GameObject, public WristerEngine::_2D::ColliderGroup
{
protected:
	std::unique_ptr<WristerEngine::_2D::Sprite> sprite;

	virtual void Initialize(const ObjectData& objData);
};