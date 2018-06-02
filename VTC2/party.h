#pragma once
#include "character_manager.h"

class Party : public CharacterManager{
public:
	int affiliationId;

	Party(int affiliationId, int id, const std::string &name) : CharacterManager(id, name)
	{
		this->affiliationId = affiliationId;

		int count = 8;
		members.reserve(count);
		for (int i = 0; i < count; i++) {
			auto character = new Character(affiliationId, id);
			allCharacters.push_back(character);
			members.push_back(character);
		}
	}
};