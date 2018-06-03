#pragma once

#include <random>

#include "game_level.h"
#include "hp_timer.h"

class GameController
{
	GameController() { mt.seed(std::random_device()()); }
	static GameLevel* currentLevel;
	static HPTimer* hpTimer;
public:
	static std::mt19937 mt;
	static bool loading;
	static void Init();
	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);
	static void Update();
	static void Render();
};