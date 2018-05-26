#pragma once

#include <vector>
#include "character.h"
#include "graphics.h"
#include "point.h"


class CharacterManager
{
public:
	std::vector<Character*> characters;

	CharacterManager();
	~CharacterManager();

	void Action();
	void Render(Graphics* graphics);
};