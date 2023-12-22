#pragma once
#include <vector>
#include <array>
#include "Assets.h"
#include "Timer.h"
#include "AnimSpriteComponent.h"
#include "BackgroundSpriteComponent.h"
#include <iostream>
using std::vector;

class Game{
public:
	static Game& instance() {
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;
	Renderer& getRenderer() { return renderer; }
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();
	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	//Game specific
	std::array<std::array<int, 8>, 8> getGrid() { return grid; }
	void setGrid(std::array<std::array<int, 8>, 8> g) { grid = g; }
	void setGridSquare(int v, int h, int x) { grid[v][h] = x; }
	void GridToString();
	Actor* getEnnemy() { return ennemy; }
	Actor* getPlayer() { return player; }

private:
	Game() :
		isRunning(true),isUpdatingActors(false){};
	void processInput(string key);
	void update(float dt);
	void render();

	Window window;
	bool isRunning;
	Renderer renderer;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	//Game specific
	std::array<std::array<int, 8>, 8> grid = { {
		{0,0,0,0,0,0,0,0},
		{0,3,-1,0,-1,-1,-1,0},
		{0,0,1,0,-1,-1,-1,0},
		{0,-1,-1,-1,-1,-1,-1,0},
		{0,-1,-1,-1,-1,-1,-1,0},
		{0,-1,-1,-1,2,-1,-1,0},
		{0,-1,-1,-1,-1,-1,-1,0},
		{0,0,0,0,0,0,0,0}
	} };
	Actor* ennemy;
	Actor* player;
};
