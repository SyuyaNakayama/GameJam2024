#include "Player.h"

using namespace WristerEngine::_2D;

void Player::Initialize()
{
	// �v���C���[�̏�����
	playerSprite = Sprite::Create("white1x1.png");
	playerSprite->size = constant->GetConstant<Vector2>("PlayerSize");
	playerSprite->position.y = WristerEngine::WIN_SIZE.y - constant->GetConstant<float>("GroundHeight");
	playerSprite->anchorPoint = { 0.5f,1.0f };
}

void Player::Update()
{

	// �v���C���[�X�v���C�g�̏�����
	playerSprite->Update();
}
