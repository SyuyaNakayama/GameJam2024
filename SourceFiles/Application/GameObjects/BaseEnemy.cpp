#include "BaseEnemy.h"
#include "NonEffectDrawer.h"
using namespace WristerEngine::_2D;

void BaseEnemy::Initialize(const ObjectData& objData)
{
	MyGameObject::Initialize(objData);

	// HPゲージ
	hpGauge = Sprite::Create("white1x1.png");
	hpGauge->size = Const(Vector2, "EnemyGaugeSize");
	hpGauge->position = objData.e_gaugePos;
	hpGauge->color = { 0,1,0,1 };

	damageShake = { -2,2 };

	maxHp = objData.e_hp;

	// コライダーの設定
	collisionAttribute = CollisionAttribute::Enemy;
	collisionMask = CollisionMask::Enemy;
	AddCollider(sprite.get(), CollisionShapeType::Box, "body");

	//WristerEngine::NonEffectDrawer::AddSprite(hpGauge.get());
}

void BaseEnemy::Update()
{
	sprite->Update();
	hpGauge->size.x = Const(Vector2, "EnemyGaugeSize").x * hpRate;
	hpGauge->Update();
}

void BaseEnemy::Draw()
{
	sprite->Draw();
	hpGauge->Draw();
}

void BaseEnemy::OnCollision(WristerEngine::_2D::ColliderGroup* collider)
{
	for (auto pair : collisionPair[0])
	{
		if (collider->GetColliderName(pair) == "attack")
		{
			hpRate -= 1.0f / maxHp;
			sprite->posOffset = { damageShake(),damageShake() };
		}
		else
		{
			sprite->posOffset = {};
		}
	}
}