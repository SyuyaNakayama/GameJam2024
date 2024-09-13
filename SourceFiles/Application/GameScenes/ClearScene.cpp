#include "ClearScene.h"
#include "SceneManager.h"
#include "ShareValue.h"

using namespace WristerEngine::_2D;

void ClearScene::Initialize()
{
	ShareValue::GetInstance()->isGoal = false;
	// UI描画クラスの初期化
	uiDrawer = std::make_unique<UIDrawerClearScene>();
	uiDrawer->Initialize();

	audio_select = WristerEngine::AudioManager::Create("select.mp3");
	bgm = WristerEngine::AudioManager::Create("gameclear.mp3", true);
	bgm->Play();
}

void ClearScene::Update()
{
	if (operate->GetTrigger("SceneChange")) {
		sceneManager->ChangeScene(Scene::Title);
		audio_select->Play();
		bgm->Stop();
	}
	// UI描画
	uiDrawer->Update();
}

void UIDrawerClearScene::Initialize()
{
	sprites["clear"] = Sprite::Create("SceneBG/GameClear.png");
	sprites["clear"]->size *= 3.0f;
	sprites["clear"]->SetCenterPos();
	sprites["clear"]->SetCenterAnchor();

	sprites["bg"] = Sprite::Create("SceneBG/background.png");
}
