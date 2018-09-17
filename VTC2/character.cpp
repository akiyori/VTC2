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
	sightRange = 100;
	attackRange = 10;
	speed = 20;
	status = Status::Free;
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

	// �G��T��
	characterInSight = targets;
	Character* target = NULL;
	for (Character* character : targets) {
		if (character->affiliationId != affiliationId && character->alive) {
			target = character;
			break;
		}
	}

	// ��ԋ߂��L�����N�^���אڂ��Ă���ꍇ�A���b�N��Ԃ�����邽�ߔ�����
	if (!targets.empty() && Point::Distance(targets[0]->position, position) < 10) {
		auto yaw = (Point::Direction(targets[0]->position, position) + Point::Rotate(Point::Direction(destination, position), 180)) / 2;
		position += yaw * speed * timeDelta;
	}
	else {
		// �ړI�n�ւ̈ړ�
		auto healthRate = (float)currentAttributes.health / maxAttributes.health;
		position += Point::Direction(position, destination) * speed * timeDelta * (healthRate< 0.2? -1:1);
	}
	
	// �G������ΖړI�n�ɐݒ肵�U������
	if (target != NULL) {
		destination = target->position;
		// �U���͈͓��Ȃ�U��
		if(attackRange >= Point::Distance(position, target->position))
			Attack(target);
	}

	// �ړI�n�֓��������ꍇ�����_���ړ�
	if (Point::Distance(position, destination) < 1) {
		destination.x += ((rand() % 100) - 50) * 10;
		destination.y += ((rand() % 100) - 50) * 10;
	}

	// �ړ��͈͐���
	position.FitRange(new Point(0, 0), new Point((float)GameSetting::MAP_WIDTH, (float)GameSetting::MAP_HEIGHT));
	destination.FitRange(new Point(0, 0), new Point((float)GameSetting::MAP_WIDTH, (float)GameSetting::MAP_HEIGHT));
}
