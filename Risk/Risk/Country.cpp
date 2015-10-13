#include <iostream>
#include <string>

#include "stdafx.h"
#include "Country.h"
#include "Player.h" 

/*
COUNTRY CLASS
Member variables:
country_name, a string representing the country's name.
owner, a pointer to the player that currently owns this country.
is_owned, a bool indicating whether this country is currently owned or not.
number_of_armies, an int indicating the number of armies currently situated in this country.

Functions:
Country(name), the Country object constructor, taking a string to initialize the country's name.
~Country(), the Country object destructor.
get_country_name(), a simple function returning a string containing the name of the country.
set_owned(value, player), a function to set the value of is_owned, and owner.
get_owner(), a function to access the current owner's Player functions.
get_owner_name(), a simple function returning a string containing the name of the owner, through the pointer in owned.
owned(), a simple function returning the current status of is_owned.
increment_armies(amt), a function to increment the number of armies situated in this country by amt.
decrement_armies(amt), a function to decrement the number of armies situated in this country by amt.
get_number_of_armies, a simple function returning an int containing the number of armies currently situated in the country.
*/

Country::Country(std::string name) {
	country_name = name;
	//Initialized to NULL as when the country is created, it does not have an owner.
	owner = NULL;
	//Initialized to false as when the country is created, it does not have an owner.
	is_owned = false;
	number_of_armies = 0;
	std::cout << get_country_name() + " Country object created." << std::endl;
}

Country::~Country() {
	std::cout << get_country_name() + " Country object destroyed." << std::endl;
}

std::string Country::get_country_name() {
	return country_name;
}

void Country::set_owned(bool value, Player& player) {
	//If value is true, then we can assign the address of the player to the Player pointer, owner.
	if(value == true) {
		is_owned = value;
		owner = &player;
	}
	//Else, set the Player pointer, owner back to NULL.
	else {
		is_owned = value;
		owner = NULL;
	}
}

Player* Country::get_owner() {
	return owner;
}

std::string Country::get_owner_name() {
	//If the Player pointer, owner is currently set to NULL, inform the system that the country has no owner.
	if(owner == NULL) {
		return "This country has no owner!";
	}
	//Else, through the Player pointer, owner, retrieve the string value of the player's name.
	else {
		return owner->get_player_name();
	}
}

bool Country::owned() {
	return is_owned;
}

void Country::increment_armies(int amt) {
	number_of_armies += amt;
}

void Country::decrement_armies(int amt) {
	//If the decrement will reduce the number of armies situated in the country to below 0, inform the system.
	if((number_of_armies - amt) < 0) {
		std::cout << "Invalid decrement. Cannot decrease the number of armies below 0" << std::endl;
	}
	//Else, decrement the number of armies by amt.
	else {
		number_of_armies -= amt;
	}
}

int Country::get_number_of_armies() {
	return number_of_armies;
}