#include "character_manager.h"
#include <thread>
#include "stopwatch.h"

CharacterManager::CharacterManager()
{
	for (int i = 0; i < 200; i++) {
		characters.push_back(new Character(0));
		characters.push_back(new Character(1));
	}
}

CharacterManager::~CharacterManager()
{
}

void CharacterManager::Update(double timeTotal, double timeDelta)
{
	for (Character* character : characters) {
		std::vector<Character*> targetInSight = {};
		for (Character* target : characters) {
			if (character->sightRange >= Point::Distance(character->position, target->position)) {
				targetInSight.push_back(target);
			}
		}
		character->Action(targetInSight);

		//std::thread t1([&targetInSight](std::vector<Character*> characters, Character* character) {
		//	for (Character* target : characters) {
		//		if (character->sightRange >= Point::Distance(character->position, target->position)) {
		//			targetInSight.push_back(target);
		//		}
		//	}
		//	character->Action(targetInSight);
		//}, characters, character);
		//t1.join();
	}
}

void CharacterManager::Render(Graphics* graphics)
{
	for (Character* character : characters) {
		graphics->DrawCircle(character->position, 4, D2D1::ColorF(character->affiliationId, 0, 1-character->affiliationId, character->alive?1:0.2));
	}
}
