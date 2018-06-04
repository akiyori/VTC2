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
	sightRange = 200;
	speed = 20;
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
			break;
		}
	}

	if (target != NULL) {
		Attack(target);
		destination = target->position;
	}

	if (!targets.empty()) {
		if (Point::Distance(targets[0]->position, position) < 10) {
			auto yaw = (Point::Direction(targets[0]->position, position) + Point::Rotate(Point::Direction(destination, position), 180))/2;
			position += yaw * speed * timeDelta;
			return;
		}
	}

	position += Point::Direction(position, destination) * speed * timeDelta;
	if(Point::Distance(position, destination) < 1){
		destination.x += (rand() % 100) - 50;
		destination.y += (rand() % 100) - 50;
	}
	position.FitRange(new Point(0, 0), new Point((float)GameSetting::MAP_WIDTH, (float)GameSetting::MAP_HEIGHT));
	destination.FitRange(new Point(0, 0), new Point((float)GameSetting::MAP_WIDTH, (float)GameSetting::MAP_HEIGHT));
}
