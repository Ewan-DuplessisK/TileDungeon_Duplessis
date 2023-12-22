#include "SimpleGridCollisionComponent.h"
#include "Pawn.h"
#include "Game.h"
#include <cassert>
#include <typeinfo>
#include <iostream>

SimpleGridCollisionComponent::SimpleGridCollisionComponent(Actor* ownerP, int updateOrder) :Component(ownerP, updateOrder) {
	Pawn* pawnA = dynamic_cast<Pawn*>(&owner);
	assert(typeid(owner) == typeid(Pawn));
}

bool Intersect(const SimpleGridCollisionComponent& a) {
	Pawn* pawnA = dynamic_cast<Pawn*>(&a.getOwner());
	std::array<int, 2> ANextPos = pawnA->getNextPos();
	//Grid[v][h]
	switch (Game::instance().getGrid()[ANextPos[0]][ANextPos[1]]) {
	case 0://mur
		pawnA->setNextPos(pawnA->getGridPos());//ne rien faire
		return true;
		break;// inutile, mis par principe
	case 1://porte
		if (pawnA->getKeys() > 0) {//ouvrir porte
			pawnA->setKeys(pawnA->getKeys() - 1);
			Game::instance().setGridSquare(ANextPos[0], ANextPos[1], -1);
			return false;
		}
		else {
			pawnA->setNextPos(pawnA->getGridPos());//ne rien faire
			return true;
		}
		break;
	case 2://clé
		if (pawnA->getIsPlayer()) {
			pawnA->setKeys(pawnA->getKeys() + 1);
			Game::instance().setGridSquare(ANextPos[0], ANextPos[1], -1);
			return false;
		}
		else {
			pawnA->setNextPos(pawnA->getGridPos());//ne rien faire
			return true;
			break;
		}
		break;
	case 3://exit
		std::cout << "You win" << std::endl;
	default: return false;
	}
}