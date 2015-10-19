#include "stdafx.h"
#include "Engine.h"


Engine::Engine()
{
	player = Player("Person"); // maybe ask the user for his name?
	startPhase();
}


Engine::~Engine()
{
}

void Engine::startPhase() {
	generateAIPlayers();
	chooseMap();
	assignCountries();
	gamePlayPhase();
}

void Engine::gamePlayPhase(){

	while (victoryConditions()) {
		reinforcementPhase();
		attackPhase();
		fortificationPhase();
	}

}



void Engine::reinforcementPhase() {

}
void Engine::attackPhase() {

}
void Engine::fortificationPhase() {

}





bool Engine::victoryConditions() {
	
	if (player.numberOfCountriesOwned() < 1)
		defeat = true;
	else {
		bool d = false;
		for (unsigned int i = 0; i < AIplayers.size(); ++i) {


			if (AIplayers[i].numberOfCountriesOwned() < 1)
				victory = true;
			else {
				victory = false;
				d = true;
			}
			if (d)
				break;

		}

	}

	if (defeat || victory)
		return false;
	else
		return true;
}
void Engine::generateAIPlayers() {
	//TODO **********************************************************************************************************************
	// ask here the user for number of players
	AIplayers.push_back(Player("AI Mister Swag"));
	AIplayers.push_back(Player("AI Mister Yolo"));
	AIplayers.push_back(Player("AI Miss Swag"));
	AIplayers.push_back(Player("AI Miss Yolo"));
}

void Engine::chooseMap() {
	//TODO **********************************************************************************************************************
	// choose the map to play on
	// countries will be generated inside the map class
	map = Map(); // for now use default one
}


void Engine::assignCountries() {
	/*
	int numberOfCountries = map.countryNumber; // need this method


	for (int i = 0; i < players.size(); ++i) {
	int x = numberOfCountries;
	while (x > 0) {
	players[i].assign_country(map.getRandomCountry());
	--x;
	}
	}


	*/
	
}




