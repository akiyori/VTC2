#include "Level1.h"

void Level1::Load()
{
	auto o1 = new Organization(0, "blue");
	auto o2 = new Organization(1, "red");
	organizations.push_back(o1);
	organizations.push_back(o2);
}

void Level1::Unload()
{
}

void Level1::Update(double timeTotal, double timeDelta)
{
	CharacterManager::Update(timeTotal, timeDelta);
}

void Level1::Render(double frameRate)
{
	CharacterManager::Render(graphics);
	graphics->DrawTextFrameRate(frameRate);
}


