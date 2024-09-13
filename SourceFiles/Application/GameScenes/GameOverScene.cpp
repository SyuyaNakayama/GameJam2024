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
	sprites["death"]->position.y -= 50;
	sprites["death"]->SetCenterAnchor();

	sprites["bg"] = Sprite::Create("SceneBG/background.png");
	sprites["bg"]->color.a = 0.5f;

	//ナビ
	sprites["navi"] = Sprite::Create("UI/gameover_guidance.png");
	sprites["navi"]->position = { WristerEngine::WIN_SIZE.x / 3,WristerEngine::WIN_SIZE.y - WEConst(float, "GroundHeight") };
	sprites["navi"]->size = WEConst(Vector2, "NaviSize");
	sprites["navi"]->isInvisible = false;
	maxAnimTime = 60;
	animTime = maxAnimTime;
}

void UIDrawerGameOverScene::Update()
{
	animTime--;
	if (animTime < 0) {
		animTime = maxAnimTime;
		if (!sprites["navi"]->isInvisible) {
			sprites["navi"]->isInvisible = true;
		}
		else {
			sprites["navi"]->isInvisible = false;
		}
	}

	AbstractUIDrawer::Update();
}
