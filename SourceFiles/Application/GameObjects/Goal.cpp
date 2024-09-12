#include "Goal.h"
#include <imgui.h>
#include <cmath>
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void Goal::Initialize(const ObjectData& objData)
{
	// ������
	sprite = Sprite::Create("treasure.png");
	MyGameObject::Initialize(objData);

	collisionAttribute = CollisionAttribute::Goal;
	collisionMask = CollisionMask::Goal;
	AddCollider(sprite.get(), CollisionShapeType::Box, "Goal");
}

void Goal::Update()
{
	// �X�v���C�g�̍X�V
	sprite->Update();
}