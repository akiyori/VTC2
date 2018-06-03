#include "game_controller.h"

GameLevel* GameController::currentLevel;
bool GameController::loading;
HPTimer* GameController::hpTimer;

void GameController::Init()
{
	loading = true;
	currentLevel = 0;
	hpTimer = new HPTimer();
}

void GameController::LoadInitialLevel(GameLevel * level)
{
	loading = true;
	currentLevel = level;
	level->Load();
	loading = false;
}

void GameController::SwitchLevel(GameLevel * level)
{
	loading = true;
	currentLevel->Unload();
	level->Load();
	delete currentLevel;
	currentLevel = level;
	loading = false;

}

void GameController::Render()
{
	if (loading) return;
	currentLevel->Render(hpTimer->frameRate);
}

void GameController::Update()
{
	if (loading) return;
	hpTimer->Update();
	//hpTimer->WaitFrame();
	currentLevel->Update(hpTimer->GetTimeTotal(), hpTimer->GetTimeDelta());
}
