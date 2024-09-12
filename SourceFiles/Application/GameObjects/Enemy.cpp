#include "Enemy.h"
#include <imgui.h>

using namespace WristerEngine::_2D;

void Enemy::Initialize(const ObjectData& objData)
{
	// 敵
	sprite = Sprite::Create("pillar.png");
	MyGameObject::Initialize(objData);

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

	Option option{};
	option.fov = Const(int, "EnemyEyeFOV");
	AddCollider(eyeBeam.get(), CollisionShapeType::TwoRay, "eyeBeam", &option);
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

void DarumaEnemy::Initialize(const ObjectData& objData)
{
	sprite = Sprite::Create("pillar.png");
	sprite->color = { 1.0f,0.5f,0.5f,1.0f };
	MyGameObject::Initialize(objData);
	sprite->isFlipX = true;

	// HPゲージ
	hpGauge = Sprite::Create("white1x1.png");
	hpGauge->size = Const(Vector2, "EnemyGaugeSize");
	hpGauge->position = Const(Vector2, "EnemyGaugePos");
	hpGauge->color = { 0,1,0,1 };

	// コライダーの設定
	collisionAttribute = CollisionAttribute::Enemy;
	collisionMask = CollisionMask::Enemy;
	AddCollider(sprite.get(), CollisionShapeType::Box, "body");

	attack = Sprite::Create("white1x1.png");
	attack->size = WristerEngine::WIN_SIZE;
	attack->isInvisible = true;
	attackInterval = Const(int, "DarumaEnemyAttackInterval");

	shakeBody = { 0,15 };
}

void DarumaEnemy::Update()
{
	if (attackInterval.Update())
	{
		attack->isInvisible = false;
		AddCollider(attack.get(), CollisionShapeType::Box, "attack");
		attackTimer= Const(int, "DarumaEnemyAttackTime");
		sprite->isFlipX = false;
		sprite->posOffset.x = 0;
	}
	else
	{
		if (attackInterval.GetRemainTimeRate() <= 0.2f)
		{
			sprite->posOffset.x = shakeBody();
		}
	}
	if (!attack->isInvisible)
	{
		if (attackTimer.Update())
		{
			sprite->isFlipX = true;
			attack->isInvisible = true;
			DeleteCollider("attack");
		}
	}

	attack->Update();
	sprite->Update();
	hpGauge->Update();
}

void DarumaEnemy::Draw()
{
	attack->Draw();
	sprite->Draw();
	hpGauge->Draw();
}
