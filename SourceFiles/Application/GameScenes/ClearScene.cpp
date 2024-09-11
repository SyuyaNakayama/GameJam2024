#include "ClearScene.h"
#include "SceneManager.h"
#include "ShareValue.h"

using namespace WristerEngine::_2D;

void ClearScene::Initialize()
{
	ShareValue::GetInstance()->isGoal = false;
	// UI�`��N���X�̏�����
	uiDrawer = std::make_unique<UIDrawerClearScene>();
	uiDrawer->Initialize();
}

void ClearScene::Update()
{
	if (operate->GetTrigger("SceneChange")) {
		sceneManager->ChangeScene(Scene::Title);
	}
	// UI�`��
	uiDrawer->Update();
}

void UIDrawerClearScene::Initialize()
{
}
