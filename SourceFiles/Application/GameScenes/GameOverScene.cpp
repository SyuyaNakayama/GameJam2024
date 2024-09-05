#include "GameOverScene.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void GameOverScene::Initialize()
{
	// UI•`‰æƒNƒ‰ƒX‚Ì‰Šú‰»
	uiDrawer = std::make_unique<UIDrawerGameOverScene>();
	uiDrawer->Initialize();
}

void GameOverScene::Update()
{
	// UI•`‰æ
	uiDrawer->Update();
}

void UIDrawerGameOverScene::Initialize()
{
}
