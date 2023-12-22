#pragma once
#include "Component.h"
class PawnGridCollisionComponent:public Component
{
public:
	PawnGridCollisionComponent(Actor* owner, int updateOrder = 3);
	PawnGridCollisionComponent() = delete;
	PawnGridCollisionComponent(const PawnGridCollisionComponent&) = delete;
	PawnGridCollisionComponent& operator=(const PawnGridCollisionComponent&) = delete;


};
int Intersect(const PawnGridCollisionComponent& a, const PawnGridCollisionComponent& b);
