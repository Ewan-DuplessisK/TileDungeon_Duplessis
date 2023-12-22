#pragma once
#include <array>
#include "Actor.h"
class PawnGridCollisionComponent;
class SimpleGridCollisionComponent;
class Pawn:public Actor
{
public:
	Pawn(std::array<int, 2> pos, int dir, int hp,bool isP);
	void setGridPos(std::array<int, 2> pos) { mGridPos = pos; }
	std::array<int, 2> getGridPos() { return mGridPos; }

	void setDirection(int dir) { mDirection = dir; }
	int getDirection() { return mDirection; }

	void setNextPos(std::array<int, 2> pos) { mNextPos = pos; }
	std::array<int, 2> getNextPos() { return mNextPos; }

	void setNextDirection(int dir) { mNextDirection = dir; }
	int getNextDirection() { return mNextDirection; }

	void hit();

	void updateActor(float dt);

	int getKeys() { return keys; }
	void setKeys(int k) { keys = k; }

	bool getIsPlayer() { return isPlayer; }

	PawnGridCollisionComponent* getPawnCollision() { return PawnCollision; }
	void setPawnCollision(PawnGridCollisionComponent* col) { PawnCollision = col; }

	SimpleGridCollisionComponent* getGridCollision() { return GridCollision; }
	void setGridCollision(SimpleGridCollisionComponent* col) { GridCollision = col; }

private:
	std::array<int, 2> mGridPos;
	int mDirection;
	std::array<int, 2> mNextPos;
	int mNextDirection;
	bool isHit=false;
	int hitPoints;
	int keys=0;
	bool isPlayer;
	PawnGridCollisionComponent* PawnCollision;
	SimpleGridCollisionComponent* GridCollision;
	//int actionSpeed;
};

