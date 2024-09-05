#include "Enemy.h"

using namespace WristerEngine::_2D;

void Enemy::Initialize()
{
	// 初期化
	sprite = Sprite::Create("white1x1.png");
	sprite->size = Const(Vector2, "EnemySize");
	sprite->position.x = Const(float, "EnemyPosX");
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };
	sprite->color = { 0.5f,0.5f,1.0f,1.0f };

}

void Enemy::Update()
{
	// スプライトの更新
	sprite->Update();
}