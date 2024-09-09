#include "Enemy.h"
#include <imgui.h>

using namespace WristerEngine::_2D;

void Enemy::Initialize()
{
	// 初期化
	sprite = Sprite::Create("TestEnemy.png");
	sprite->size = Const(Vector2, "EnemySize");
	sprite->position.x = Const(float, "EnemyPosX");
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };
	sprite->color = { 1.0f,1.0f,1.0f,1.0f };

	eyeBeam = Sprite::Create("EyeBeam.png");
	eyeBeam->size.y = 1000;
	eyeBeam->position = Const(Vector2, "EnemyEyePos");
	eyeBeam->anchorPoint = { 0.5f,0.0f };
	eyeBeam->color = { 1.0f,1.0f,1.0f,1.0f };
	eyeBeam->rotation = Angle(30);

	// コライダーの設定
	collisionAttribute = CollisionAttribute::Enemy;
	collisionMask = CollisionMask::Enemy;
	AddCollider(sprite.get(), CollisionShapeType::Box, "body");
}

void Enemy::Update()
{
	// スプライトの更新
	sprite->Update();
	eyeBeam->Update();
}

void Enemy::OnCollision([[maybe_unused]] WristerEngine::_2D::ColliderGroup* collider)
{
	for (auto pair : collisionPair[0])
	{
		ImGui::Text("%s", collider->GetColliderName(pair).c_str());
	}
}
