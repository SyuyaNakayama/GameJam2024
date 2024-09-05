#include "GameOverScene.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void GameOverScene::Initialize()
{
	// UI描画クラスの初期化
	uiDrawer = std::make_unique<UIDrawerGameOverScene>();
	uiDrawer->Initialize();
}

void GameOverScene::Update()
{
	// UI描画
	uiDrawer->Update();
}

void UIDrawerGameOverScene::Initialize()
{
}
