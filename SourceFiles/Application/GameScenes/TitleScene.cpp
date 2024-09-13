#include "TitleScene.h"
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void TitleScene::Initialize()
{
	// UI描画クラスの初期化
	uiDrawer = std::make_unique<UIDrawerTitleScene>();
	uiDrawer->Initialize();

	//背景
	bg = Sprite::Create("title_background.png");
	//キャラ
	player = Sprite::Create("Player/drill_girl.png");
	player->size = WEConst(Vector2, "EffectSize");
	player->SetAnimation(4, 60);
	player->position = { 200,WristerEngine::WIN_SIZE.y - WEConst(float, "GroundHeight") };
	player->anchorPoint = { -0.5f,1.0f };

	walk = Sprite::Create("Player/drill_girl_walk.png");
	walk->size = WEConst(Vector2, "WalkSize");
	walk->SetAnimation(6, 5);
	walk->anchorPoint = { -0.5f, 1.0f };
	walk->position = player->position;

	wait = 180;
	isStart = false;
	//ロゴ
	logo = Sprite::Create("UI/logo.png");
	logo->position = { WristerEngine::WIN_SIZE.x / 2 - 10.0f,WEConst(float, "GroundHeight") / 2 };
	logo->size = WEConst(Vector2, "LogoSize");
	//ナビ
	navi = Sprite::Create("UI/title_guidance.png");
	navi->position = { WristerEngine::WIN_SIZE.x / 3,WristerEngine::WIN_SIZE.y - WEConst(float, "GroundHeight") };
	navi->size = WEConst(Vector2, "NaviSize");
	navi->isInvisible = false;
	maxAnimTime = 60;
	animTime = maxAnimTime;

	chargeMove = 0.5f;
	isUDChange = false;

	audio_select = WristerEngine::AudioManager::Create("select.mp3");
	bgm = WristerEngine::AudioManager::Create("title.mp3", true);
	bgm->Play();
}

void TitleScene::Update()
{
	animTime--;
	if (animTime < 0) {
		animTime = maxAnimTime;
		if (!navi->isInvisible) {
			navi->isInvisible = true;
		}
		else {
			navi->isInvisible = false;
		}
	}

	if (operate->GetTrigger("SceneChange")) {
		animTime = 2;
		maxAnimTime = 2;
		isStart = true;
		audio_select->Play();
		bgm->Stop();
	}
	if (isStart) {
		wait--;
		walk->position.x += 3.0f;
		if (wait < 0) {
			sceneManager->ChangeScene(Scene::Tutorial);
		}
	}
	logo->position.y += chargeMove;
	if (!isUDChange) {
		chargeMove -= 0.01f;
	}
	else {
		chargeMove += 0.01f;
	}
	if (chargeMove < -0.5f) {
		isUDChange = true;
	}
	else if (chargeMove > 0.5f) {
		isUDChange = false;
	}

	// UI描画
	//uiDrawer->Update();
	//アニメーション描画
	bg->Update();
	player->Update();
	logo->Update();
	navi->Update();
	walk->Update();
}

void TitleScene::Draw() {
	bg->Draw();
	if (!isStart) {
		player->Draw();
	}
	else{
		walk->Draw();
	}
	logo->Draw();
	navi->Draw();
}

void UIDrawerTitleScene::Initialize()
{
	sprites["title"] = Sprite::Create("title_background.png");
	sprites["title"]->SetCenterPos();
	sprites["title"]->SetCenterAnchor();
}