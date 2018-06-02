#pragma once

#include <vector>
#include <string>
#include "character.h"
#include "graphics.h"
#include "point.h"

class CharacterManager
{
public:
	static std::vector<Character*> allCharacters;

	int id;
	std::string name;
	std::vector<Character*> members;
	Point destination;

	CharacterManager() {}
	CharacterManager(int id, const std::string &name);
	~CharacterManager();

	static void Update(double timeTotal, double timeDelta);
	static void Render(Graphics* graphics);
};