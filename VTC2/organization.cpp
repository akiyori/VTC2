#include "organization.h"

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

void Organization::AddCharacter(Point postion)
{
	parties.back()->AddCharacter(postion);
}
