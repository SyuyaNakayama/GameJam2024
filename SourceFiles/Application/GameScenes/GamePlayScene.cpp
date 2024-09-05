#include "GamePlayScene.h"

using namespace WristerEngine::_2D;

void GamePlayScene::Initialize()
{
	stage.Initialize();
	// UI描画クラスの初期化
	uiDrawer = std::make_unique<UIDrawerGamePlayScene>();
	uiDrawer->Initialize();
}

void GamePlayScene::Update()
{
	stage.Update();
	// UI描画
	uiDrawer->Update();
}

void GamePlayScene::Draw()
{
	stage.Draw();
	// UI描画
	uiDrawer->Draw();
}

void UIDrawerGamePlayScene::Initialize()
{
	// 地面のUIの初期化
	sprites["Ground"] = Sprite::Create("white1x1.png");
	std::unique_ptr<Sprite>& s = sprites["Ground"];
	s->size.x = WristerEngine::WIN_SIZE.x;
	s->size.y = constant->GetConstant<float>("GroundHeight");
	s->position.y = WristerEngine::WIN_SIZE.y - s->size.y;
}
