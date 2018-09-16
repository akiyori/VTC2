#pragma once

#include <string>
#include <utility>
#include <vector>
#include "point.h"
#include "character_attributes.h"

class Character
{
public:
	int id;
	int affiliationId;
	int partyId;
	bool alive;
	std::string name;
	CharacterAttributes maxAttributes;
	CharacterAttributes currentAttributes;
	Point position;
	Point destination;
	int speed;
	int sightRange;
	std::vector<Character*> characterInSight;
	bool selected;

	Character(int affiliationId, int partyId);
	~Character();

	void Attack(Character* target);
	void AttackMultiple(std::vector<Character*> targets);
	void OnAttacked(Character* attacker);
	void OnDead();
	void Action(std::vector<Character*> targets, double timeDelta);
};