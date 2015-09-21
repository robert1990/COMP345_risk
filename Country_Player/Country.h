#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>
//#include "Player.h"

class Country {
private:
	std::string country_name;
	//Player country_owner;
	int number_of_armies;
public:
	Country(std::string name);
	std::string get_country_name();
	/*Public for now, however I think this function should be handled by startup phase and or battle mechanisms*/
	//void assign_owner(Player player);
	//Player get_country_owner();
	int get_number_of_armies();
	/*I feel these next 3 functions should be encapsulated somehow.
	Setting armies should be the handled by the initial startup phase of the game
		==> or maybe not even exist? increment_armies essentially would do the same thing
	Incrementing/decrementing should be handled both by battle and fortification mechanisms
	For now, they will be public for demonstration purposes*/
	void set_armies(int amount);
	void increment_armies(int amount);
	void decrement_armies(int amount);
};

#endif