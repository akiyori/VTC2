#pragma once

#include "party.h"

class Organization : public CharacterManager {
public:
	std::vector<Party*> parties;

	Organization(int id, const std::string &name) : CharacterManager(id, name) 
	{
		int count = 16;
		parties.reserve(count);
		for (int i = 0; i < count; i++) {
			auto party = new Party(id, i, "party" + std::to_string(i));
			parties.push_back(party);
		}
	}

	void Update(double timeTotal, double timeDelta);

	void Render(Graphics* graphics);
};