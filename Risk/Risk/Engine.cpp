#include "stdafx.h"
#include "Engine.h"


Engine::Engine()
{
	cout << "Assignment: creating engine and game state" << endl;
	gameState = GameState("Person"); // maybe ask the user for his name?
	startPhase();
}


Engine::~Engine()
{
}

void Engine::startPhase() {
	cout << "Assignment: starting game..." << endl;
	generateAIPlayers();
	chooseMap();
	assignCountries();
	gamePlayPhase();
}

void Engine::gamePlayPhase(){
	cout << "Assignment: playing the game!" << endl;
	while (victoryConditions()) {
		reinforcementPhase();
		attackPhase();
		fortificationPhase();
	}

}



void Engine::reinforcementPhase() {
	gameState.changeGamePhase(Phase(GETTING));


}
void Engine::attackPhase() {
	gameState.changeGamePhase(Phase(ATTACKING));


}
void Engine::fortificationPhase() {
	gameState.changeGamePhase(Phase(FORTIFYING));


}





bool Engine::victoryConditions() {
	
	if (gameState.getCurrentPlayer.numberOfCountriesOwned() < 1)
		defeat = true;
	else {
		bool d = false;
		vector<Player> v = gameState.getAIPlayers();
		for (unsigned int i = 0; i < v.size(); ++i) {


			if (v[i].numberOfCountriesOwned() < 1)
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
	gameState.addPlayer("AI Mister Swag");
	gameState.addPlayer("AI Mister Yolo");
	gameState.addPlayer("AI Miss Swag");
	gameState.addPlayer("AI Miss Yolo");
}

void Engine::chooseMap() {
	//TODO **********************************************************************************************************************
	// choose the map to play on
	// countries will be generated inside the map class
	string s = "Default_Map";
	gameState.setMap(s);
}


void Engine::assignCountries() {
	gameState.generateCountries();
}




