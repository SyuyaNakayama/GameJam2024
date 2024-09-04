#include "GamePlayScene.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void GamePlayScene::Initialize()
{
	uiDrawer = std::make_unique<UIDrawerGamePlayScene>();
	uiDrawer->Initialize();
}

void GamePlayScene::Update()
{
	uiDrawer->Update();
}

void UIDrawerGamePlayScene::Initialize()
{
}
