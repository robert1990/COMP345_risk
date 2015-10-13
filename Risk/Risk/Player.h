#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

#include "Country.h"
#include "Deck.h"

class Player {
private:
	/*Member variables*/
	std::string player_name;
	
	std::vector<Country*> countries_owned;
	
	/*May possible have to refactor the hand logic to be a vector of pointers, similar to Country*/
	std::vector<Deck::Card> hand;
public:
	Player(std::string name);
	~Player();
	std::string get_player_name();
	
	void assign_country(Country& country);
	void remove_country(Country& country);
	std::string print_countries_owned();
	
	void add_to_hand(Deck::Card);
	void cash_cards(Deck& deck);
	void view_hand();
};

#endif