#pragma once

#include <vector>
#include "game_level.h"
#include "organization.h"
#include "character_manager.h"
#include "rectangle.h"

class Level1 : public GameLevel
{
	std::vector<Organization*> organizations;
public:
	virtual void Load() override;
	virtual void Unload() override;
	virtual void Update(double timeTotal, double timeDelta) override;
	virtual void Render(double frameRate) override;
};