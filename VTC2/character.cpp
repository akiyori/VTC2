#include "character.h"

Character::Character(int affiliationId)
{
	this->affiliationId = affiliationId;
	this->partyId = 1;
	alive = true;
	maxAttributes.health = 10;
	maxAttributes.strength = 1;
	currentAttributes = maxAttributes;
	position.x = affiliationId * 500 + rand() % 50;
	position.y = affiliationId * 500 + rand() % 50;
	destination.x = (1-affiliationId) * 500;
	destination.y = (1-affiliationId) * 500;
	sightRange = 200;
	speed = 2;
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

void Character::Action(std::vector<Character*> targets)
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
		double rate = (double)speed / Point::Distance(position, destination);
		if (rate < 1) 
		{
			position += (destination - position) * rate;
		}
		else 
		{
			position = destination;
		}
	}
	else 
	{
		destination.x += (rand() % 100)-50;
		destination.y += (rand() % 100) - 50;
	}
}
