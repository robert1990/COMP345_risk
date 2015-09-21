#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

//class Country;

class Player {
private:
	std::string player_name;
	//std::vector<Country> countries_owned;
public:
	Player(std::string name);
	std::string get_player_name();
	//void add_to_countries_owned(Country country);
	//void remove_from_countries_owned(Country country);
};

#endif