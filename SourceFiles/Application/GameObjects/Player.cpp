#include "Player.h"

void Player::Initialize()
{
	// �v���C���[�̏�����
	playerSprite->size = constant->GetConstant<Vector2>("PlayerSize");
	playerSprite->position.y = WristerEngine::WIN_SIZE.y - constant->GetConstant<float>("GroundHeight");
}

void Player::Update()
{

	// �v���C���[�X�v���C�g�̏�����
	playerSprite->Update();
}
