#include "Goal.h"
#include <imgui.h>
#include <cmath>
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void Goal::Initialize() 
{
	// 初期化
	sprite = Sprite::Create("TestGoal.png");
	sprite->size = Const(Vector2, "PlayerSize");
	sprite->position.x = Const(float, "GoalPosX");
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };

	collisionAttribute = CollisionAttribute::Goal;
	collisionMask = CollisionMask::Goal;
	AddCollider(sprite.get(), CollisionShapeType::Box, "Goal");
}

void Goal::Update()
{
	// スプライトの更新
	sprite->Update();
}