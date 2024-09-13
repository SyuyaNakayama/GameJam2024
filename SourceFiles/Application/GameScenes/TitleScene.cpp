#include "TitleScene.h"
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void TitleScene::Initialize()
{
	// UI•`‰æƒNƒ‰ƒX‚Ì‰Šú‰»
	uiDrawer = std::make_unique<UIDrawerTitleScene>();
	uiDrawer->Initialize();

	//”wŒi
	bg = Sprite::Create("title_background.png");
	//ƒLƒƒƒ‰
	player = Sprite::Create("Player/drill_girl.png");
	player->size = WEConst(Vector2, "EffectSize");
	player->SetAnimation(4, 60);
	player->position = { 200,WristerEngine::WIN_SIZE.y - WEConst(float, "GroundHeight") };
	player->anchorPoint = { -0.5f,1.0f };
	//ƒƒS
	logo = Sprite::Create("UI/logo.png");
	logo->position = { WristerEngine::WIN_SIZE.x / 2,WEConst(float, "GroundHeight") / 2 };
	logo->size = WEConst(Vector2, "LogoSize");

	chargeMove = 0.5f;
	isUDChange = false;

	audio_select = WristerEngine::AudioManager::Create("select.mp3");
	bgm = WristerEngine::AudioManager::Create("title.mp3", true);
	bgm->Play();
}

void TitleScene::Update()
{
	if (operate->GetTrigger("SceneChange")) {
		sceneManager->ChangeScene(Scene::Tutorial);
		audio_select->Play();
		bgm->Stop();
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

	// UI•`‰æ
	//uiDrawer->Update();
	//ƒAƒjƒ[ƒVƒ‡ƒ“•`‰æ
	bg->Update();
	player->Update();
	logo->Update();
}

void TitleScene::Draw() {
	bg->Draw();
	player->Draw();
	logo->Draw();
}

void UIDrawerTitleScene::Initialize()
{
	sprites["title"] = Sprite::Create("title_background.png");
	sprites["title"]->SetCenterPos();
	sprites["title"]->SetCenterAnchor();
}