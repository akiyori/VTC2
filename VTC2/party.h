#pragma once
#include "character_manager.h"

class Party : public CharacterManager{
public:
	int affiliationId;

	Party(int affiliationId, int id, const std::string &name) : CharacterManager(id, name)
	{
		this->affiliationId = affiliationId;
		destination = Point((id+1) * 100, (1 - affiliationId) * 600 + 100);

		int count = 8;
		members.reserve(count);
		for (int i = 0; i < count; i++) {
			auto character = new Character(affiliationId, id);
			character->position = GetPartyPosition(Point((id + 1) * 100, affiliationId * 600 + 100), destination, i);
			character->destination = destination;
			allCharacters.push_back(character);
			members.push_back(character);
		}
	}

	Point GetPartyPosition(Point base, Point target, int index){
		float distanceRate = 5;
		auto dir = Point::Direction(base, target);
		Point diff = Point(0, 0);
		switch (index)
		{
		case 0:
			break;
		case 1:
			diff = Point::Rotate(dir, -30) * 2;
			break;
		case 2:
			diff = Point::Rotate(dir, 30) * 2;
			break;
		case 3:
			diff = Point::Rotate(dir, -60) * 3.4;
			break;
		case 4:
			diff = Point::Rotate(dir, 60) * 3.4;
			break;
		case 5:
			diff = dir * 3.4;
			break;
		case 6:
			diff = Point::Rotate(dir, -30) * 3.4;
			break;
		case 7:
			diff = Point::Rotate(dir, 30) * 3.4;
			break;
		default:
			return Point(0, 0);
		}
		return base + diff * distanceRate;
	}
};