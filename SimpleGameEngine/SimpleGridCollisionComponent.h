#pragma once
#include "Component.h"
class SimpleGridCollisionComponent :public Component
{
public:
	SimpleGridCollisionComponent(Actor* owner, int updateOrder = 4);
	SimpleGridCollisionComponent() = delete;
	SimpleGridCollisionComponent(const SimpleGridCollisionComponent&) = delete;
	SimpleGridCollisionComponent& operator=(const SimpleGridCollisionComponent&) = delete;

};
bool Intersect(const SimpleGridCollisionComponent& a);
