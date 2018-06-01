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

	void Update(double timeTotal, double timeDelta);
	void Render(Graphics* graphics);
};