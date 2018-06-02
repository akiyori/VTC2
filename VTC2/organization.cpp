#include "organization.h"
//
//Organization::Organization(int id, const std::string & name)
//{
//	CharacterManager::CharacterManager(id, name);
//	
//}
void Organization::Update(double timeTotal, double timeDelta)
{
	for (auto party : parties) {
		party->Update(timeTotal, timeDelta);
	}
}

void Organization::Render(Graphics* graphics)
{
	for (auto party : parties) {
		party->Render(graphics);
	}
}
