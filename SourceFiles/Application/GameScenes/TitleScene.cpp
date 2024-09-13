#include "TitleScene.h"
#include "SceneManager.h"

using namespace WristerEngine::_2D;

void TitleScene::Initialize()
{
	// UI•`‰æƒNƒ‰ƒX‚Ì‰Šú‰»
	uiDrawer = std::make_unique<UIDrawerTitleScene>();
	uiDrawer->Initialize();

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
	// UI•`‰æ
	uiDrawer->Update();
}

void UIDrawerTitleScene::Initialize()
{
	sprites["title"] = Sprite::Create("title_background.png");
	sprites["title"]->SetCenterPos();
	sprites["title"]->SetCenterAnchor();
}