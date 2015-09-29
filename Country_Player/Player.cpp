#include <iostream>
#include <vector>
#include <string>

#include "Player.h"
#include "Country.h"

Player::Player(std::string name) {
	player_name = name;
	std::cout << get_player_name() + " Player object created." << std::endl;
}

Player::~Player() {
	std::cout << get_player_name() + " Player object destroyed." << std::endl;
}

std::string Player::get_player_name() {
	return player_name;	
}

void Player::assign_country(Country& country) {
	if(country.owned() == false) {
		countries_owned.push_back(&country);
		country.set_owned(true);
	}
	else {
		std::cout << "Please remove the country from the current player whom owns it" << std::endl;
	}
}

void Player::remove_country(Country& country) {
	int index = -1;
	int num_of_countries_owned = countries_owned.size();
	for(int i=0; i<num_of_countries_owned; i++) {
		if(countries_owned.at(i) == &country) {
			index = i;
		}
	}
	if(index == -1) {
		std::cout << "Country was not found. Cannot remove a country that does not exist!" << std::endl;
	}
	else {
		countries_owned.erase(countries_owned.begin()+index);
		country.set_owned(false);
	}
}

std::string Player::print_countries_owned() {
	std::string countries = "";
	int size = countries_owned.size();
	if(size == 0) {
		countries = "no countries found";
	}
	else {
		for(int i=0; i<size; i++) {
			//Country c(countries_owned.at(i));
			//countries = countries_owned.at(0)->get_country_name();
			if(i != size-1) {
				//countries += countries_owned.at(i).get_country_name() + ", ";
				countries += countries_owned.at(i)->get_country_name() + ", ";
			}
			else {
				//countries += countries_owned.at(i).get_country_name();
				countries += countries_owned.at(i)->get_country_name();
			}
		}
	}
	return countries;
}