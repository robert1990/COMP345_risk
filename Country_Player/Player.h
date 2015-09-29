#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

class Country;

class Player {
private:
	std::string player_name;
	std::vector<Country*> countries_owned;
public:
	Player(std::string name);
	~Player();
	std::string get_player_name();
	std::string print_countries_owned();
	void assign_country(Country& country);
	void remove_country(Country& country);
};

#endif