#pragma once
#include "MoveComponent.h"
#include <SDL_stdinc.h>

class GridMoveComponent : public MoveComponent {
public:
	GridMoveComponent(Actor* ownerP, int updateOrder = 2);
	GridMoveComponent() = delete;
	GridMoveComponent(const GridMoveComponent&) = delete;
	GridMoveComponent& operator=(const GridMoveComponent&) = delete;

	void update(float dt) override;
};

