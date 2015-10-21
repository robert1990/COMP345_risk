#include "stdafx.h"
#include "GameState.h"


GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::addPlayer(std::string name) {
	players.push_back(Player(name));
}

void GameState::changeGamePhase(Phase newPhase) {

}

void GameState::updatePlayerTurn() {

}
Player* GameState::getCurrentPlayer() {
	// TODO : Create actual method, this is just to prevent error when compiling
	return new Player();
}