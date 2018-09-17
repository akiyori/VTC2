#include "party.h"

void Party::AddCharacter(Point position)
{
	auto character = new Character(affiliationId, id);
	character->position = position;
	character->destination = position;
	allCharacters.push_back(character);
	members.push_back(character);
}
