#include "ClearScene.h"
#include "SceneManager.h"
#include "ShareValue.h"
#include "PostEffect.h"

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

	PostEffect::GetPostEffect(0)->SetEffectType(PostEffect::Type::None);
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
	sprites["clear"]->position.y -= 50;
	sprites["clear"]->SetCenterAnchor();

	sprites["bg"] = Sprite::Create("SceneBG/background.png");

	//ナビ
	sprites["navi"] = Sprite::Create("UI/gameover_guidance.png");
	sprites["navi"]->position = { WristerEngine::WIN_SIZE.x / 2,WristerEngine::WIN_SIZE.y - WEConst(float, "GroundHeight") };
	sprites["navi"]->size = WEConst(Vector2, "NaviSize");
	sprites["navi"]->size.x /= 2.0f;
	sprites["navi"]->isInvisible = false;
	sprites["navi"]->anchorPoint.x = 0.5f;
	sprites["navi"]->textureSize.x = 144;
	maxAnimTime = 60;
	animTime = maxAnimTime;
}

void UIDrawerClearScene::Update()
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
