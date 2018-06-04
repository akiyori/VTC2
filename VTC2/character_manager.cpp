#include "character_manager.h"
#include <thread>
#include "stopwatch.h"
#include <string> 
#include "spdlog/spdlog.h"

std::vector<Character*> CharacterManager::allCharacters;
std::vector<std::vector<int>> CharacterManager::map;

CharacterManager::CharacterManager(int id, const std::string &name)
{
	this->id = id;
	this->name = name;
	map = std::vector<std::vector<int>>(MAP_SIZE, std::vector<int>(MAP_SIZE, -1));
}

CharacterManager::~CharacterManager()
{
}

void CharacterManager::Update(double timeTotal, double timeDelta)
{
	{
		StopWatch<std::chrono::milliseconds> sw("reset map");

		for (auto& row : map) {
			std::fill(row.begin(), row.end(), -1);
		}
	}
	{
		StopWatch<std::chrono::milliseconds> sw("create map");

		for (size_t i = 0, n = allCharacters.size(); i < n; ++i) {
			auto* character = allCharacters[i];
			map[(int)character->position.x][(int)character->position.y] = i;
		}
	}
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
		if (character->alive) {
			Point start = character->position + Point::Rotate(Point(0, -1), -60) * 6;
			Point end = character->position + Point::Rotate(Point(0, -1), 60) * 6;
			end.y += 2;
			graphics->FillRectangle(start, end, 1,0,0,1);
			auto width = (end.x - start.x) * ((float)character->currentAttributes.health / character->maxAttributes.health);
			graphics->FillRectangle(start, Point(start.x + width, end.y), 0, 1, 0, 1);
		}
	}
}
