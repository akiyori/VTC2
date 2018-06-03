#include "character.h"
#include "game_setting.h"

Character::Character(int affiliationId, int partyId)
{
	this->affiliationId = affiliationId;
	this->partyId = partyId;
	alive = true;
	maxAttributes.health = 100;
	maxAttributes.strength = 1;
	currentAttributes = maxAttributes;
	position.x = (float)(rand() % GameSetting::MAP_WIDTH);
	position.y = (float)(rand() % GameSetting::MAP_HEIGHT);
	destination.x = (float)(1-affiliationId) * 500;
	destination.y = (float)(1-affiliationId) * 500;
	sightRange = 200;
	speed = 60;
}

Character::~Character()
{
}

void Character::Attack(Character* target)
{
	if(target->alive)
		target->OnAttacked(this);
}

void Character::AttackMultiple(std::vector<Character*> targets)
{
	for (Character* target : targets) {
		Attack(target);
	}
}

void Character::OnAttacked(Character* attacker)
{
	currentAttributes.health -= attacker->currentAttributes.strength;
	if (currentAttributes.health <= 0)
		OnDead();
}

void Character::OnDead()
{
	alive = false;
}

void Character::Action(std::vector<Character*> targets, double timeDelta)
{
	if (!alive) return;
	characterInSight = targets;
	Character* target = NULL;
	for (Character* character : targets) {
		if (character->affiliationId != affiliationId && character->alive) {
			target = character;
			Attack(target);
			break;
		}
	}

	if (target != NULL)
		destination = target->position;

	if (position != destination) {
		auto rate = speed / Point::Distance(position, destination) * timeDelta;
		if (rate < 1) 
		{
			position += (destination - position) * (float)rate;
		}
		else 
		{
			position = destination;
		}
	}
	else 
	{
		destination.x += (rand() % 100) - 50;
		destination.y += (rand() % 100) - 50;
		destination.FitRange(new Point(0,0), new Point((float)GameSetting::MAP_WIDTH, (float)GameSetting::MAP_HEIGHT));
	}
}
