#pragma once

#include <random>

#include "graphics.h"
#include "character_manager.h"

class Game
{
public:
	CharacterManager* characterManager;
	std::mt19937 mt;

	Game();
	~Game();

	void Start();
	void Tick();
	void Render(Graphics* graphics);
};