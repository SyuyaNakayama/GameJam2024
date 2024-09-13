#include "GameOverScene.h"
#include "SceneManager.h"
#include "ShareValue.h"

using namespace WristerEngine::_2D;

void GameOverScene::Initialize()
{
	ShareValue::GetInstance()->isGameOver = false;
	// UI描画クラスの初期化
	uiDrawer = std::make_unique<UIDrawerGameOverScene>();
	uiDrawer->Initialize();

	audio_select = WristerEngine::AudioManager::Create("select.mp3");
	bgm = WristerEngine::AudioManager::Create("gameover.mp3", true);
	bgm->Play();
}

void GameOverScene::Update()
{
	if (operate->GetTrigger("SceneChange")) {
		sceneManager->ChangeScene(Scene::Play);
		audio_select->Play();
		bgm->Stop();
	}
	// UI描画
	uiDrawer->Update();
}

void UIDrawerGameOverScene::Initialize()
{
	sprites["death"] = Sprite::Create("SceneBG/GameOver.png");
	sprites["death"]->size *= 3.0f;
	sprites["death"]->SetCenterPos();
	sprites["death"]->SetCenterAnchor();
}
