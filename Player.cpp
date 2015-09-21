#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Player.h"
//#include "Country.h"

Player::Player(std::string name) {
	player_name = name;
	//countries_owned;
}

std::string Player::get_player_name() {
	return player_name;
}

//void Player::add_to_countries_owned(Country country) {
//	countries_owned.push_back(country);
//}
//
//void Player::remove_from_countries_owned(Country country) {
//	Country c = std::find(countries_owned.begin(), countries_owned.end(), country);
//}