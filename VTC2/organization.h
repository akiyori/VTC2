#pragma once

#include "party.h"

class Organization : public CharacterManager {

	Point GetPartyPosition(Point base, Point target, int index) {
		float distanceRate = 100;
		auto dir = Point::Direction(base, target);
		Point diff = Point(0, 0);
		switch (index)
		{
		case 0:
			break;
		case 1:
			diff = Point::Rotate(dir, -90);
			break;
		case 2:
			diff = Point::Rotate(dir, 90);
			break;
		case 3:
			diff = Point::Rotate(dir, -30);
			break;
		case 4:
			diff = Point::Rotate(dir, 30);
			break;
		case 5:
			diff = Point::Rotate(dir, -90) * 2;
			break;
		case 6:
			diff = Point::Rotate(dir, 90) * 2;
			break;
		case 7:
			diff = Point::Rotate(dir, -60) * 1.732;
			break;
		case 8:
			diff = Point::Rotate(dir, 60) * 1.732;
			break;
		case 9:
			diff = Point::Rotate(dir, 0) * 1.732;
			break;
		case 10:
			diff = Point::Rotate(dir, -30) * 2;
			break;
		case 11:
			diff = Point::Rotate(dir, 30) * 2;
			break;
		default:
			return Point(0, 0);
		}
		return base + diff * distanceRate;
	}
public:
	std::vector<Party*> parties;

	Organization(int id, const std::string &name) : CharacterManager(id, name) 
	{
		int count = 12;
		parties.reserve(count);
		auto base = Point(1280/2, 100+id*600);
		destination = Point(1280 / 2, 100 + (1-id) * 600);
		for (int i = 0; i < count; i++) {
			auto party = new Party(id, i, "party" + std::to_string(i), GetPartyPosition(base, destination, i));
			parties.push_back(party);
		}
	}

	void Update(double timeTotal, double timeDelta);

	void Render(Graphics* graphics);
};