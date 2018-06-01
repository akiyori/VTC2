#pragma once

#include "game_level.h"
#include "character_manager.h"

class Level1 : public GameLevel
{
	CharacterManager* characterManager;
public:
	virtual void Load() override;
	virtual void Unload() override;
	virtual void Update(double timeTotal, double timeDelta) override;
	virtual void Render() override;
};