#include "SceneFactory.h"
#include "TitleScene.h"
#include "TutorialScene.h"
#include "GamePlayScene.h"
#include "GameOverScene.h"
#include "ClearScene.h"
#include <cassert>

SceneFactory* SceneFactory::GetInstance()
{
	static SceneFactory instance;
	return &instance;
}

std::unique_ptr<WristerEngine::BaseScene> SceneFactory::CreateScene(Scene scene)
{
	std::unique_ptr<WristerEngine::BaseScene> newScene;

	switch (scene)
	{
	case Scene::Title: newScene = std::make_unique<TitleScene>(); break;
	case Scene::Tutorial: newScene = std::make_unique<TutorialScene>(); break;
	case Scene::Play: newScene = std::make_unique<GamePlayScene>(); break;
	case Scene::GameOver: newScene = std::make_unique<GameOverScene>(); break;
	case Scene::Clear: newScene = std::make_unique<ClearScene>(); break;
	}

	assert(newScene);
	return newScene;
}