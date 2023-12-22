#include "Pawn.h"
#include "Assets.h"
#include "PawnGridCollisionComponent.h"
#include "SimpleGridCollisionComponent.h"
#include "Game.h"

Pawn::Pawn(std::array<int, 2> pos, int dir, int hp,bool isP) :Actor(), mGridPos(pos), mDirection(dir), mNextPos(pos), mNextDirection(dir), hitPoints(hp),isPlayer(isP){
}

void Pawn::hit() {
	this->isHit = true;
	this->hitPoints--;
}

void Pawn::updateActor(float dt){
	Pawn* pawnB;
	if (isPlayer) {
		pawnB = dynamic_cast<Pawn*>(getGame().getEnnemy());
	}
	else {
		pawnB = dynamic_cast<Pawn*>(getGame().getPlayer());
	}
	Intersect(*PawnCollision, *pawnB->getPawnCollision());
	if (!Intersect(*GridCollision)) {
		mGridPos = mNextPos;
		mDirection = mNextDirection;
	}
	Vector2 pos;
	pos.set(mGridPos[0]*64.0,mGridPos[1]*64.0);
	setPosition(pos);
	setRotation(mDirection * 90.0);
}
