#include "TutorialScene.h"
#include "ShareValue.h"
#include "CollisionManager.h"

using namespace WristerEngine::_2D;

void TutorialScene::Initialize()
{
	ShareValue::GetInstance()->stageNum = 1;
	stage.Initialize();

	background = Sprite::Create("SceneBG/background.png");
	background->size = WristerEngine::WIN_SIZE;
	background->Update();
	
	uiDrawer = std::make_unique<UIDrawerTutorialScene>();
	uiDrawer->Initialize();
	bgm = WristerEngine::AudioManager::Create("stageBGM.mp3", true);
	bgm->Play();
}

void TutorialScene::Update()
{
	ShareValue* shareVal = ShareValue::GetInstance();

	if (shareVal->isGoal)
	{
		shareVal->isGoal = false;
		shareVal->stageNum++;
		sceneManager->ChangeScene(Scene::Play);
		bgm->Stop();
		return;
	}

	if (shareVal->isGameOver)
	{
		sceneManager->ChangeScene(Scene::GameOver);
		bgm->Stop();
		return;
	}

	stage.Update();

	uiDrawer->Update();
}

void TutorialScene::Draw()
{
	background->Draw();
	stage.Draw();
	uiDrawer->Draw();
}

void UIDrawerTutorialScene::Initialize()
{
	// ’n–Ê‚ÌUI‚Ì‰Šú‰»
	sprites["Ground"] = Sprite::Create("brick.png");
	std::unique_ptr<Sprite>& s = sprites["Ground"];
	s->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	s->textureSize.x *= (WristerEngine::WIN_SIZE.x / s->size.x);
	s->textureSize.y *= (Const(float, "GroundHeight") / s->size.y);
	s->size.x = WristerEngine::WIN_SIZE.x;
	s->size.y = Const(float, "GroundHeight");
}
