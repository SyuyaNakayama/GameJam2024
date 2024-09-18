#include "TitleScene.h"
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void TitleScene::Initialize()
{
	// UI•`‰æƒNƒ‰ƒX‚Ì‰Šú‰»
	uiDrawer = std::make_unique<UIDrawerTitleScene>();
	uiDrawer->Initialize();

	//”wŒi
	bg = Sprite::Create("SceneBG/title_background.png");
	//ƒLƒƒƒ‰
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
	//ƒƒS
	logo = Sprite::Create("UI/logo.png");
	logo->position = { WristerEngine::WIN_SIZE.x / 2 - 10.0f,WEConst(float, "GroundHeight") / 2 };
	logo->size = WEConst(Vector2, "LogoSize");
	//ƒiƒr
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

	if (operate->GetTrigger("SceneChange") && !isStart) {
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

	//ƒAƒjƒ[ƒVƒ‡ƒ“•`‰æ
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
	else {
		walk->Draw();
	}
	logo->Draw();
	navi->Draw();
	// UI•`‰æ
	uiDrawer->Draw();
}

void UIDrawerTitleScene::Initialize()
{
	sprites["version"] = Sprite::Create("UI/version.png");
	sprites["version"]->position = Const(Vector2, "VersionPos");
	sprites["version"]->Update();
}