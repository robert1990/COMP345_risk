#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
using std::vector;
enum Phase {
	GETTING,
	ATTACKING,
	FORTIFYING
};
class GameState
{
public:

	GameState();
	GameState(std::string name);
	~GameState();
	void addPlayer(std::string name);
	void changeGamePhase(Phase newPhase);
	void updatePlayerTurn();
	Player getMainPlayer();
	Player* getCurrentPlayer();
	vector<Player> getAIPlayers();
	void setMap(string str);
	void generateCountries();

private:
	Player player;
	vector<Player> AIPlayers;
	Map map;
	Phase currentPhase;
	// TODO: Not sure which data type here yet, look into that - C
	int currentPlayerTurn;
};

