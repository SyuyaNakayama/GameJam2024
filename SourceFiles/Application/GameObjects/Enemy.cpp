#include "Enemy.h"
#include <imgui.h>

using namespace WristerEngine::_2D;

void Enemy::Initialize()
{
	// 敵
	sprite = Sprite::Create("TestEnemy.png");
	sprite->size = Const(Vector2, "EnemySize");
	sprite->position.x = Const(float, "EnemyPosX");
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };
	sprite->color = { 1.0f,1.0f,1.0f,1.0f };

	// ビーム
	eyeBeam = Sprite::Create("EyeBeam.png");
	eyeBeam->size.y = 1000;
	eyeBeam->position = Const(Vector2, "EnemyEyePos");
	eyeBeam->anchorPoint = { 0.5f,0.0f };
	eyeBeam->color = { 1.0f,1.0f,1.0f,1.0f };
	eyeBeam->rotation = Angle(30);
	
	beamRotEasing.Initialize(120, WristerEngine::Easing::Type::Linear);
	beamRotEasing.SetLoop(30);

	// HPゲージ
	hpGauge = Sprite::Create("white1x1.png");
	hpGauge->size = Const(Vector2, "EnemyGaugeSize");
	hpGauge->position = Const(Vector2, "EnemyGaugePos");
	hpGauge->color = { 0,1,0,1 };

	// コライダーの設定
	collisionAttribute = CollisionAttribute::Enemy;
	collisionMask = CollisionMask::Enemy;
	AddCollider(sprite.get(), CollisionShapeType::Box, "body");
}

void Enemy::Update()
{
	hpGauge->size.x = Const(Vector2, "EnemyGaugeSize").x * hpRate;
	eyeBeam->rotation = beamRotEasing.Update() * Angle(30) + Angle(30);

	// スプライトの更新
	sprite->Update();
	eyeBeam->Update();
	hpGauge->Update();
}

void Enemy::Draw()
{
	sprite->Draw();
	eyeBeam->Draw();
	hpGauge->Draw();
}

void Enemy::OnCollision([[maybe_unused]] WristerEngine::_2D::ColliderGroup* collider)
{
	for (auto pair : collisionPair[0])
	{
		if (collider->GetColliderName(pair) != "attack") { return; }

		hpRate -= 0.01f;
	}
}
