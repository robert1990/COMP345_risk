#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"


class GameState
{
public:
	enum Phase{
		GETTING,
		ATTACKING,
		FORTIFYING
	};
	GameState();
	~GameState();
	void addPlayer(std::string name);
	void changeGamePhase(Phase newPhase);
	void updatePlayerTurn();
	Player* getCurrentPlayer();

private:
	std::vector<Player> players;
	Map map;
	Phase currentPhase;
	// TODO: Not sure which data type here yet, look into that - C
	int currentPlayerTurn;
};

