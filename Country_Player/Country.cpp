#include <iostream>
#include <string>
#include "Country.h"
//#include "Player.h"

Country::Country(std::string name) {
	country_name = name;
	number_of_armies = 0;
}

std::string Country::get_country_name() {
	return country_name;
}

//void Country::assign_owner(Player player) {
//	country_owner = player;
//	player.add_to_countries_owned(*this);
//}
//
//Player Country::get_country_owner() {
//	return country_owner;
//}

int Country::get_number_of_armies() {
	return number_of_armies;
}

void Country::set_armies(int amount) {
	if(amount < 0) {
		std::cout << "Not a valid amount" << std::endl;
	}
	else {
		number_of_armies = amount;
	}
}

void Country::increment_armies(int amount) {
	if(amount < 0) {
		std::cout << "Not a valid amount" << std::endl;
	}
	else {
		number_of_armies += amount;
	}
}

void Country::decrement_armies(int amount) {
	int valid_amount = number_of_armies - amount;
	if(amount < 0 || valid_amount < 0) {
		std::cout << "Not a valid amount" << std::endl;
	}
	else {
		number_of_armies -= amount;
	}
}