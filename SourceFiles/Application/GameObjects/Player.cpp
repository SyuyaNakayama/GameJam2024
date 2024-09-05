#include "Player.h"

void Player::Initialize()
{
	// プレイヤーの初期化
	playerSprite->size = constant->GetConstant<Vector2>("PlayerSize");
	playerSprite->position.y = WristerEngine::WIN_SIZE.y - constant->GetConstant<float>("GroundHeight");
}

void Player::Update()
{

	// プレイヤースプライトの初期化
	playerSprite->Update();
}
