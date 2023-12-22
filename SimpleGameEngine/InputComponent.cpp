#include "InputComponent.h"
#include <SDL_scancode.h>
#include<array>
#include <cassert>
#include <typeinfo>
#include "Pawn.h"
#include <iostream>

InputComponent::InputComponent(Actor* ownerP,int updateOrder) :
	Component(ownerP,updateOrder),
	upKey(SDL_SCANCODE_Z),
	downKey(SDL_SCANCODE_S),
	leftKey(SDL_SCANCODE_Q),
	rightKey(SDL_SCANCODE_D)
{
	Pawn* pawnA = dynamic_cast<Pawn*>(&owner);
	assert(typeid(owner)==typeid(Pawn));
}

void InputComponent::processInput(/*const Uint8* keyState*/int Nkey) {
	Pawn* pawnA = dynamic_cast<Pawn*>(&this->getOwner());
	if (/*keyState[upKey]*/Nkey==0)
	{
		pawnA->setNextDirection(0);
	}
	if (/*keyState[downKey]*/Nkey==2)
	{
		pawnA->setNextDirection(2);
	}
	if (/*keyState[leftKey]*/Nkey==1)
	{
		pawnA->setNextDirection(1);//Direction dans le sens anti horaire pour avoir le plus petit nombre du côté négatif de chaque axe
	}
	if (/*keyState[rightKey] */Nkey==3 ) {
		pawnA->setNextDirection(3);
	}

	std::cout << pawnA->getNextDirection() << std::endl;
	std::cout << pawnA->getNextPos()[0] << " " << pawnA->getNextPos()[1] << std::endl;
}


void InputComponent::setUpKey(int key) {
	upKey = key;
}

void InputComponent::setDownKey(int key) {
	downKey = key;
}

void InputComponent::setLeftKey(int key) {
	leftKey = key;
}

void InputComponent::setRightKey(int key) {
	rightKey = key;
}

/*void InputComponent::update(const Uint8* keyState) {
	processInput(keyState);
}*/