#include "Player.h"

using namespace WristerEngine::_2D;

void Player::Move()
{
	const float MOVE_SPD = Const(float, "PlayerMoveSpd");
	float moveDir = (float)operate->GetPush("Right") - operate->GetPush("Left");
	sprite->position += moveDir * MOVE_SPD;
}

void Player::Initialize()
{
	// 初期化
	sprite = Sprite::Create("white1x1.png");
	sprite->size = Const(Vector2, "PlayerSize");
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };
	sprite->color = { 0.5f,1.0f,0.5f,1.0f };
}

void Player::Update()
{
	Move();
	// スプライトの更新
	sprite->Update();
}
