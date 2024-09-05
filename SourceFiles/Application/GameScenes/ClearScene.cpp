#include "ClearScene.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void ClearScene::Initialize()
{
	// UI描画クラスの初期化
	uiDrawer = std::make_unique<UIDrawerClearScene>();
	uiDrawer->Initialize();
}

void ClearScene::Update()
{
	// UI描画
	uiDrawer->Update();
}

void UIDrawerClearScene::Initialize()
{
}
