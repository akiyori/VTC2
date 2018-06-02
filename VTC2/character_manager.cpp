#include "character_manager.h"
#include <thread>
#include "stopwatch.h"
#include <string> 
#include "spdlog/spdlog.h"

CharacterManager::CharacterManager()
{
	int count = 100;
	characters.reserve(count *2);
	for (int i = 0; i < count; i++) {
		characters.push_back(new Character(0));
		characters.push_back(new Character(1));
	}

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

		for (size_t i = 0, n = characters.size(); i < n; ++i) {
			auto* character = characters[i];
			map[character->position.x][character->position.y] = i;
		}
	}
	{
		StopWatch<std::chrono::milliseconds> sw("target process");
		//std::string r = "";
		//std::string c = "";
		//auto logger = spdlog::get("async_file_logger");
		//for (auto row : map) {
		//	for (auto cell : row) {
		//		r.append(std::to_string(cell)).push_back(',');
		//	}
		//	logger->info(r);
		//	r = "";
		//}
		
		for (Character* character : characters)
		{
			std::vector<Character*> targetInSight = {};
			targetInSight.reserve(64);
			int startX = character->position.x - character->sightRange / 2;
			int endX = character->position.x + character->sightRange / 2;
			int startY = character->position.y - character->sightRange / 2;
			int endY = character->position.y + character->sightRange / 2;
			if (startX < 0) startX = 0;
			if (endX >= 1000) endX = 1000 - 1;
			if (startY < 0) startY = 0;
			if (endY >= 1000) endY = 1000 - 1;
			for (int x = startX; x < endX; ++x)
			{
				for (int y = startY; y < endY; ++y)
				{
					if(map[x][y] > 0)
						targetInSight.push_back(characters[map[x][y]]);
				}
			}
			character->Action(targetInSight, timeDelta);
		}
	}
}

void CharacterManager::Render(Graphics* graphics)
{
	for (Character* character : characters) {
		graphics->DrawCircle(character->position, 4, D2D1::ColorF(character->affiliationId, 0, 1-character->affiliationId, character->alive?1:0.2));
	}
}
