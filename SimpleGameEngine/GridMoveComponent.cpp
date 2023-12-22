#include "GridMoveComponent.h"
#include "Pawn.h"
#include <array>
#include <cassert>
#include <typeinfo>
#include <iostream>

GridMoveComponent::GridMoveComponent(Actor* ownerP, int updateOrder) :MoveComponent(ownerP, updateOrder) {
	Pawn* pawnA = dynamic_cast<Pawn*>(&owner);
	assert(typeid(owner) == typeid(Pawn));
}

void GridMoveComponent::update(float dt) {
	Pawn* pawnA = dynamic_cast<Pawn*>(&this->getOwner());
	std::array<int, 2> APos = pawnA->getGridPos();
	switch (pawnA->getNextDirection())
	{
	case 0:
		pawnA->setNextPos(std::array<int, 2> {APos[0] - 1, APos[1]});
		break;
	case 2:
		pawnA->setNextPos(std::array<int, 2>{APos[0] + 1, APos[1]});
		break;
	case 1:
		pawnA->setNextPos(std::array<int, 2> {APos[0], APos[1] - 1});
		break;
	case 3:
		pawnA->setNextPos(std::array<int, 2> {APos[0], APos[1] + 1});
		break;
	default:
		break;
	}
}