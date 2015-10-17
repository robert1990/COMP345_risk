#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "stdafx.h"
#include "Player.h"
#include "CardCashing.h"

/*
PLAYER CLASS
Member variables:
player_name, a string representing the player's name.
countries_owned, a vector of pointers to Country objects which the player currently owns.
hand, a vector of Card objects (a struct defined in Deck), each card represents a card the player currently owns.

Functions:
Player(name), the Player object constructor, taking a string to initialize the player's name.
~Player(), the Player object destructor.
get_player_name(), a simple function returning a string containing the name of the player.
assign_country(country), pushes the address of a country to the countries_owned vector, representing the acquisition of a country.
remove_country(country), erases the address of a country from the countries_owned vector, representing the loss of an acquired country.
print_countries_owned(), a simple function returning a string containing the names of the countries the player currently owns.
add_to_hand(Card), pushes the value of a card to the hand vector, representing the acquisiton of a card.
cash_cards(deck), returns a certain number of cards from the player's hand to the deck, following the logic defined in the CardCashing namespace.
view_hand(), a simple function returning a string containing the values of the Card IDs currently stored in the player's hand.
*/

Player::Player() {
	player_name = "Default player";
	std::cout << get_player_name() + " Player object created." << std::endl;
}

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
	//If the country is not currently owned, the player can acquire the country.
	if(country.owned() == false) {
		countries_owned.push_back(&country);
		//Set the country to being owned by this player.
		country.set_owned(true, *this);
	}
	//Else, inform the system that the acquisition cannot be completed as the country is still owned.
	else {
		std::cout << "Please remove the country from the current player whom owns it" << std::endl;
	}
}

void Player::remove_country(Country& country) {
	//An arbitrary value to be used to indicate whether the country was found in the player's countries_owned vector.
	int index = -1;
	int num_of_countries_owned = countries_owned.size();
	for(int i=0; i<num_of_countries_owned; i++) {
		//If the pointer's address in the countries_owned vector is equivalent to the address of the country passed, store the index.
		if(countries_owned.at(i) == &country) {
			index = i;
		}
	}
	//If the country was not found (index is -1), then inform the system that the country attempting to be removed does not belong to this player.
	if(index == -1) {
		std::cout << "Country was not found. Cannot remove a country that you do not own!" << std::endl;
	}
	//Else, the country is owned by the player and can be removed.
	else {
		countries_owned.erase(countries_owned.begin()+index);
		//Set the country to no longer being owned by this player.
		country.set_owned(false, *this);
	}
}

std::string Player::print_countries_owned() {
	std::string countries = "";
	int size = countries_owned.size();
	//If the size of the countries_owned vector is 0, then the player owns no countries.
	if(size == 0) {
		countries = "no countries found";
	}
	//Else, for each country the player owns, store the name of that country into the countries string.
	else {
		for(int i=0; i<size; i++) {
			if(i != size-1) { //Formatting
				countries += countries_owned.at(i)->get_country_name() + ", "; 
			}
			else { //Formatting
				countries += countries_owned.at(i)->get_country_name(); 
			}
		}
	}
	return countries;
}

/*Utility function, used in add_to_hand in order to sort the contents.*/
bool comparison_function(Deck::Card c1, Deck::Card c2) { return (c1.card_id < c2.card_id); }

void Player::add_to_hand(Deck::Card card) {
	hand.push_back(card);
	//Sorting the contents of hand for ease of viewing as well as optimizing any search functions on the hand.
	std::sort(hand.begin(), hand.end(), comparison_function);
}

//TODO
void Player::cash_cards(Deck& deck) {
	std::vector<int> amt_ids = CardCashing::count_ids(hand);
	std::vector<bool> true_ids = CardCashing::assess_where_true(hand);
	bool condition1 = CardCashing::test_condition1(hand);
	bool condition2 = CardCashing::test_condition2(hand);
	if((condition1 == true) && (condition2 == false)) {
		CardCashing::cash_on_condition1(hand, deck);
		std::cout << get_player_name() + " has received TODO armies by cashing their cards!" << std::endl;
	}
	else if((condition1 == false) && (condition2 == true)) {
		CardCashing::cash_on_condition2(hand, deck);
		std::cout << get_player_name() + " has received TODO armies by cashing their cards!" << std::endl;
	}
	else if((condition1 == true) && (condition2 == true)) {
		int choice = CardCashing::condition_choice();
		if(choice == 1) { CardCashing::cash_on_condition1(hand, deck); std::cout << get_player_name() + " has received TODO armies by cashing their cards!" << std::endl; }
		else { CardCashing::cash_on_condition2(hand, deck); std::cout << get_player_name() + " has received TODO armies by cashing their cards!" << std::endl; }
	}
	else { std::cout << "Cannot cash cards based on this hand." << std::endl; }
}

void Player::view_hand() {
	int hand_size = hand.size();
	//If the size of hand is 0, then the player does not currently have any cards.
	if(hand_size == 0) {
		std::cout << get_player_name() + " does not currently have any cards!" << std::endl;
	}
	//Else, for each card in the player's hand, print the ID of that card.
	else {
		std::cout << get_player_name() + "'s hand currently contains: ";
		for(int i=0; i<hand_size; i++) {
			if(i != hand_size-1) {
				std::cout << hand.at(i).card_id << ", "; //Formatting
			}
			else {
				std::cout << hand.at(i).card_id << std::endl; //Formatting
			}
		}
	}
}

int Player::numberOfCountriesOwned() {
	return countries_owned.size();
}