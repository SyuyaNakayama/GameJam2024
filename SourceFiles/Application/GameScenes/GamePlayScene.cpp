#include "GamePlayScene.h"

using namespace WristerEngine::_2D;

void GamePlayScene::Initialize()
{
	stage.Initialize();
	// UI•`‰æƒNƒ‰ƒX‚Ì‰Šú‰»
	uiDrawer = std::make_unique<UIDrawerGamePlayScene>();
	uiDrawer->Initialize();
}

void GamePlayScene::Update()
{
	stage.Update();
	// UI•`‰æ
	uiDrawer->Update();
}

void GamePlayScene::Draw()
{
	stage.Draw();
	// UI•`‰æ
	uiDrawer->Draw();
}

void UIDrawerGamePlayScene::Initialize()
{
	// ’n–Ê‚ÌUI‚Ì‰Šú‰»
	sprites["Ground"] = Sprite::Create("white1x1.png");
	std::unique_ptr<Sprite>& s = sprites["Ground"];
	s->size.x = WristerEngine::WIN_SIZE.x;
	s->size.y = Const(float, "GroundHeight");
	s->position.y = WristerEngine::WIN_SIZE.y - s->size.y;
}
