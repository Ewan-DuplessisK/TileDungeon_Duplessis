#include "Game.h"
#include <algorithm>
#include "Pawn.h"
#include "SpriteComponent.h"
#include "SimpleGridCollisionComponent.h"
#include "PawnGridCollisionComponent.h"
#include "GridMoveComponent.h"
#include "InputComponent.h"


bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool IsRendererInit = renderer.initialize(window);

	int windowHeight = window.getHeight();
	int windowWidth = window.getWidth();

	return isWindowInit; // Return bool && bool && bool ...to detect error
}

void Game::close(){
	renderer.close();
	window.close();
	SDL_Quit();
}



void Game::update(float dt) {
	// Update actors
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor: pendingActors){
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();
	// Delete dead actors
	vector <Actor*> deadActors;
	for (auto actor : actors) {
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors){
		delete deadActor;
	}
}

void Game::addActor(Actor* actor){
	if (isUpdatingActors){
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor) {
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors)) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

void Game::render(){
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::load() {
	Assets::loadTexture(renderer, "Res\\Player.png", "Player");
	Assets::loadTexture(renderer, "Res\\Ennemy.png", "Ennemy");
	Assets::loadTexture(renderer, "Res\\Ground.png", "Ground");
	Assets::loadTexture(renderer, "Res\\Wall.png", "Wall");
	Assets::loadTexture(renderer, "Res\\Door.png", "Door");
	Assets::loadTexture(renderer, "Res\\Key.png", "Key");

	//Single sprite
	/*auto actor = new Actor();
	auto sprite = new SpriteComponent(actor, Assets::getTexture("ship01"));
	actor->setPosition(Vector2{ 100,100 });*/
	

	// Animated sprite
	/*
		vector<Texture*> animTextures{
		&Assets::getTexture("ship01"),
		&Assets::getTexture("ship02"),
		&Assets::getTexture("ship03"),
		&Assets::getTexture("ship04"),
	};*/

	//Player
	Pawn* player = new Pawn(std::array<int, 2> {4, 1}, 3, 3, true);
	player->addComponent(new SpriteComponent(player, Assets::getTexture("Player")));
	player->addComponent(new GridMoveComponent(player));
	PawnGridCollisionComponent* Pcol = new PawnGridCollisionComponent(player);
	player->addComponent(Pcol);
	player->setPawnCollision(Pcol);
	SimpleGridCollisionComponent* Gcol =new SimpleGridCollisionComponent(player);
	player->addComponent(Gcol);
	player->setGridCollision(Gcol);
	player->addComponent(new InputComponent(player));
	this->player = player;

	//Ennemy
	Pawn* ennemy = new Pawn(std::array<int, 2>{2, 5}, 2, 1,false);
	ennemy->addComponent(new SpriteComponent(ennemy, Assets::getTexture("Ennemy")));
	ennemy->addComponent(new GridMoveComponent(ennemy)); 
	PawnGridCollisionComponent* PcolE =new PawnGridCollisionComponent(ennemy);
	ennemy->addComponent(PcolE);
	ennemy->setPawnCollision(PcolE);
	SimpleGridCollisionComponent* GcolE =new SimpleGridCollisionComponent(ennemy);
	ennemy->addComponent(GcolE);
	ennemy->setGridCollision(GcolE);
	this->ennemy = ennemy;

	// Background
	// Create the "far back" background
	/*vector<Texture*> bgTexsFar{
		&Assets::getTexture("Farback01"),
		&Assets::getTexture("Farback02")
	};*/
	/*Actor* bgFar = new Actor();
	BackgroundSpriteComponent* bgSpritesFar = new BackgroundSpriteComponent(bgFar, bgTexsFar);
	bgSpritesFar->setScrollSpeed(-100.0f);

	// Create the closer background
	Actor* bgClose = new Actor();
	std::vector<Texture*> bgTexsClose{
	&Assets::getTexture("Stars"),
	&Assets::getTexture("Stars")
	};
	BackgroundSpriteComponent * bgSpritesClose = new BackgroundSpriteComponent(bgClose, bgTexsClose, 50);
	bgSpritesClose->setScrollSpeed(-200.0f);*/

	
}

void Game::unload(){
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}
	// Resources
	Assets::clear();
}

void Game::GridToString() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; i < 8; i++) {
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Game::processInput(string key) {
	// SDL Event
	/*SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}*/
	// Keyboard state
	int Nkey=-1;
	if (key == "z") {
		Nkey = 0;
	}
	else if (key == "s") {
		Nkey = 2;
		std::cout << key << std::endl;
	}
	else if (key == "q") {
		Nkey = 1;
		std::cout << key << std::endl;
	}
	else if (key == "d") {
		Nkey = 3;
		std::cout << key << std::endl;
	}
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}

	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(/*keyboardState*/Nkey);
	}
	isUpdatingActors = false;
}

void Game::loop() {
	Timer timer;
	float dt = 0;
	string key;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		std::cin >> key;
		processInput(key);
		GridToString();
		update(dt);
		render();
		timer.delayTime();
	}
}