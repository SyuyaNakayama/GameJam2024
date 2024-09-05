#include "GamePlayScene.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void GamePlayScene::Initialize()
{
	// UI�`��N���X�̏�����
	uiDrawer = std::make_unique<UIDrawerGamePlayScene>();
	uiDrawer->Initialize();
}

void GamePlayScene::Update()
{
	// UI�`��
	uiDrawer->Update();
}

void UIDrawerGamePlayScene::Initialize()
{
	// �n�ʂ�UI�̏�����
	sprites["Ground"] = Sprite::Create("white1x1.png");
	std::unique_ptr<Sprite>& s = sprites["Ground"];
	s->size.x = WristerEngine::WIN_SIZE.x;
	s->size.y = constant->GetConstant<float>("GroundHeight");
	s->position.y = WristerEngine::WIN_SIZE.y - s->size.y;
}
