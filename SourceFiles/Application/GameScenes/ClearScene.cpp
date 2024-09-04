#include "ClearScene.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void ClearScene::Initialize()
{
	uiDrawer = std::make_unique<UIDrawerClearScene>();
	uiDrawer->Initialize();
}

void ClearScene::Update()
{
	uiDrawer->Update();
}

void UIDrawerClearScene::Initialize()
{
}
