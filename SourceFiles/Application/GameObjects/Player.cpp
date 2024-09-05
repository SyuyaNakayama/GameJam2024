#include "Player.h"

using namespace WristerEngine::_2D;

void Player::Move()
{
	const float MOVE_SPD = Const(float, "PlayerMoveSpd");
	float moveDir = (float)operate->GetPush("Right") - operate->GetPush("Left");
	playerSprite->position += moveDir * MOVE_SPD;
}

void Player::Initialize()
{
	// プレイヤーの初期化
	playerSprite = Sprite::Create("white1x1.png");
	playerSprite->size = Const(Vector2, "PlayerSize");
	playerSprite->position.y = WristerEngine::WIN_SIZE.y - constant->GetConstant<float>("GroundHeight");
	playerSprite->anchorPoint = { 0.5f,1.0f };
}

void Player::Update()
{
	Move();
	// プレイヤースプライトの初期化
	playerSprite->Update();
}
