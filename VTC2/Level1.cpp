#include "Level1.h"

void Level1::Load()
{
	characterManager = new CharacterManager();
}

void Level1::Unload()
{
	delete characterManager;
}

void Level1::Update(double timeTotal, double timeDelta)
{
	characterManager->Update(timeTotal, timeDelta);
}

void Level1::Render()
{
	characterManager->Render(graphics);
}


