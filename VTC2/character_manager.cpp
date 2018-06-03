#include "character_manager.h"
#include <thread>
#include "stopwatch.h"
#include <string> 
#include "spdlog/spdlog.h"

std::vector<Character*> CharacterManager::allCharacters;

CharacterManager::CharacterManager(int id, const std::string &name)
{
	this->id = id;
	this->name = name;
}

CharacterManager::~CharacterManager()
{
}

void CharacterManager::Update(double timeTotal, double timeDelta)
{
	{
		StopWatch<std::chrono::milliseconds> sw("serch target");

		for (Character* character : allCharacters) {
			if (!character->alive) continue;
			std::vector<Character*> targetInSight = {};
			targetInSight.reserve(300);
			for (Character* target : allCharacters) {
				if (character != target && target->alive && character->sightRange >= Point::Distance(character->position, target->position)) {
					auto pos = std::find_if(targetInSight.begin(), targetInSight.end(), [target,character](auto c) {
						return Point::Distance(character->position, c->position) > Point::Distance(character->position, target->position);
					});
					targetInSight.insert(pos, target);
				}
			}
			character->Action(targetInSight, timeDelta);
		}
	}
}

void CharacterManager::Render(Graphics* graphics)
{
	for (Character* character : allCharacters) {
		graphics->DrawCircle(
			character->position
			, 4
			, D2D1::ColorF((float)character->affiliationId, 0, (float)1-character->affiliationId, character->alive ? 1 : 0.2f)
		);
		graphics->DrawTextVTC(
			std::to_string(character->partyId)
			, character->position
			, D2D1::ColorF(1, 1, 1, character->alive ? 1 : 0.2f)
		);
	}
}
