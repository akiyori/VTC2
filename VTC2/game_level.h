#pragma once

#include "graphics.h"
#include "input.h"

class GameLevel
{
protected :
	static Graphics* graphics;
public:
	static void Init(Graphics* graphics) { GameLevel::graphics = graphics; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(double timeTotal, double timeDelta) = 0;
	virtual void Render(double frameRate) = 0;
};