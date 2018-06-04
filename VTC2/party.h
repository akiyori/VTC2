#pragma once
#include "character_manager.h"

class Party : public CharacterManager{

	Point GetPartyPosition(Point base, Point target, int index) {
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
public:
	int affiliationId;

	Party(int affiliationId, int id, const std::string &name, Point basePosition) : CharacterManager(id, name)
	{
		this->affiliationId = affiliationId;
		destination.x = basePosition.x;
		destination.y = basePosition.y * (affiliationId>0? -1:6);

		int count = 8;
		members.reserve(count);
		for (int i = 0; i < count; i++) {
			auto character = new Character(affiliationId, id);
			character->position = GetPartyPosition(basePosition, destination, i);
			character->destination = destination;
			allCharacters.push_back(character);
			members.push_back(character);
		}
	}
};