#include "PawnGridCollisionComponent.h"
#include "Pawn.h"
#include "Game.h"
#include <array>
#include <cassert>
#include <typeinfo>
#include<iostream>

PawnGridCollisionComponent::PawnGridCollisionComponent(Actor* ownerP,int updateOrder):Component(ownerP,updateOrder) {
	Pawn* pawnA = dynamic_cast<Pawn*>(&owner);
	assert(typeid(owner) == typeid(Pawn));
}

int Intersect(const PawnGridCollisionComponent& a, const PawnGridCollisionComponent& b) {
	Pawn* pawnA = dynamic_cast<Pawn*>(&a.getOwner());
	std::array<int, 2> APos = pawnA->getGridPos();
	std::array<int, 2> ANextPos = pawnA->getNextPos();
	int ADir = pawnA->getDirection();
	int ANextDir = pawnA->getNextDirection();

	Pawn* pawnB = dynamic_cast<Pawn*>(&b.getOwner());
	std::array<int, 2> BPos = pawnB->getGridPos();
	int BDir = pawnB->getDirection();

	if (ANextPos[0] == BPos[0] && ANextPos[1] == BPos[1]) {//if the pawnA walks into pawnB
		if (abs(ANextDir - BDir) == 2) {// and pawnB is looking at pawnA
			pawnA->setNextPos(APos);//Don't do anything
			return 1;
		}
		else {//if pawnB is looking in another direction
			pawnB->hit();
			if (ANextDir % 2 == 0) {//push B horizontally
				pawnB->setNextPos(std::array<int, 2> {BPos[0], BPos[1] + (ANextDir - 1)});
			}
			else {//push B vertically
				pawnB->setNextPos(std::array<int, 2> {BPos[0] + (ANextDir - 2), BPos[1] });
			}
			return 0;
		}
	}
	else return -1;
	
}
