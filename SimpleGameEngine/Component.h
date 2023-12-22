#pragma once
#include <SDL_stdinc.h>

class Actor;
class Component {
public:
	Component(Actor* owner, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }
	Actor& getOwner() const { return owner; }

	virtual void update(float dt);
	virtual void processInput(/*const Uint8* keyState*/int Nkey);
protected:
	Actor& owner;
	int updateOrder;
	// Order of the component in the actor' updateComponent method
};