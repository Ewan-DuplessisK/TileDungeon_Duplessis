#pragma once
#include "Component.h"
#include <SDL_stdinc.h>

class InputComponent:public Component {
public:
	InputComponent(Actor* ownerP,int updateOrder =1);
	InputComponent() = delete;
	InputComponent(const InputComponent&) = delete;
	InputComponent& operator=(const InputComponent&) = delete;

	void processInput(/*const Uint8* keyState*/int Nkey);

	void setUpKey(int key);
	void setDownKey(int key);
	void setLeftKey(int key);
	void setRightKey(int key);
	void update(const Uint8* keyState);
private:
	int upKey;
	int downKey;
	int leftKey;
	int rightKey;
};
