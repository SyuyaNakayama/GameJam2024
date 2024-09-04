#include "GameOverScene.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void GameOverScene::Initialize()
{
	uiDrawer = std::make_unique<UIDrawerGameOverScene>();
	uiDrawer->Initialize();
}

void GameOverScene::Update()
{
	uiDrawer->Update();
}

void UIDrawerGameOverScene::Initialize()
{
}
