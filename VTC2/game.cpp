#include "game.h"

Game::Game()
{
	mt.seed(std::random_device()());
}

Game::~Game()
{
}

void Game::Start()
{
	characterManager = new CharacterManager();
}

void Game::Tick()
{
	characterManager->Action();
}

void Game::Render(Graphics* graphics)
{
	characterManager->Render(graphics);
}

