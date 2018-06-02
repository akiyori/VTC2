#pragma once

#include <vector>
#include "character.h"
#include "graphics.h"
#include "point.h"

class CharacterManager
{
public:
	static const int MAP_SIZE = 1000;
	std::vector<Character*> characters;
	std::vector<std::vector<int>> map;

	CharacterManager();
	~CharacterManager();

	void Update(double timeTotal, double timeDelta);
	void Render(Graphics* graphics);
};