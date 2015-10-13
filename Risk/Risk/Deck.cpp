#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

#include "stdafx.h"
#include "Deck.h"

/*
DECK CLASS
Member variables:
max_deck_size, a const int set to 30 to indicate the max deck size (10 of ID 0, 10 of ID 1, 10 of ID 2).
current_deck, a vector of Cards representing the game deck.

Member functions:
initialize_deck(), a function which creates 30 cards (10 of ID 0, 10 of ID 1, 10 of ID 2) and then pushes them to current_deck. 
shuffle_deck(), a function which randomly orders cards in current_deck

Structs:
Card, a simple struct representing a Card which has only one variable, its ID. 

Functions:
Deck(), the Deck object constructor, which uses initialize_deck() and shuffle_deck() to set up current_deck.
~Deck(), the Deck object destructor.
draw_card(), a function which acts as the drawing mechanism by returning a card from the top of current_deck.
return_card(card), a function which acts as the returning mechanism by taking the card to be returned as a parameter, and returning it to the deck and then shuffling the deck.
*/

Deck::Deck() {
	std::cout << "Deck object created" << std::endl;
	Deck::initialize_deck();
	Deck::shuffle_deck();
}

Deck::~Deck() {
	std::cout << "Deck object destroyed" << std::endl;
}

void Deck::initialize_deck() {
	for(int i=0; i<max_deck_size; i++) {
		int id = i%3;
		Card card;
		card.card_id = id;
		current_deck.push_back(card);
	}
	
	/*Testing
	std::cout << "Deck initialized. Current contents:" << std::endl;
	std::cout << "Deck size: " << current_deck.size() << std::endl;
	std::cout << "Card IDs: ";
	for(unsigned int i=0; i<current_deck.size(); i++) {
		std::cout << current_deck.at(i).card_id << " ";
		if(i==current_deck.size()-1) {
			std::cout << "\n";
		}
	}*/
}

void Deck::shuffle_deck() {
	std::srand(unsigned (std::time(0)));
	std::random_shuffle(current_deck.begin(), current_deck.end());
	
	/*Testing
	std::cout << "Deck shuffled. Current contents:" << std::endl;
	std::cout << "Deck size: " << current_deck.size() << std::endl;
	std::cout << "Card IDs: ";
	for(unsigned int i=0; i<current_deck.size(); i++) {
		std::cout << current_deck.at(i).card_id << " ";
		if(i==current_deck.size()-1) {
			std::cout << "\n";
		}
	}*/
}

Deck::Card Deck::draw_card() {
	//If the deck size is 0, then there is no way to draw from the deck.
	if(current_deck.size() == 0) {
		std::cout << "Cannot draw from an empty deck!" << std::endl;
		//Create a card to be returned with ID equal to 3, indicating an error.
		Card card;
		card.card_id = 3;
		return card;
	}
	//Else, store a copy of the card located at the back of current_deck, and pop_back on current_deck.
	else {
		Card card = current_deck.back();
		current_deck.pop_back();

		/*Testing
		std::cout << "Card drawn. Current contents:" << std::endl;
		std::cout << "Deck size: " << current_deck.size() << std::endl;
		std::cout << "Card IDs: ";
		for(unsigned int i=0; i<current_deck.size(); i++) {
			std::cout << current_deck.at(i).card_id << " ";
			if(i==current_deck.size()-1) {
				std::cout << "\n";
			}
		}
		std::cout << "ID of the card drawn: " << card.card_id << std::endl;*/

		//Return the copy
		return card;
	}
}

void Deck::return_card(Card card) {
	//If current_deck's size is already at max, a player somehow ended up with a card that did not come from the deck.
	if(current_deck.size() == max_deck_size) {
		std::cout << "The deck is at max size! How did you manage to have more cards than the deck even contained?" << std::endl;
	}
	//Else, insert the card back into current_deck and perform shuffle_deck().
	else {
		std::cout << "ID of the card returned: " << card.card_id << std::endl;
		current_deck.insert(current_deck.begin(), card);
		Deck::shuffle_deck();

		/*Testing
		std::cout << "Card returned. Current contents:" << std::endl;
		std::cout << "Deck size: " << current_deck.size() << std::endl;
		std::cout << "Card IDs: ";
		for(unsigned int i=0; i<current_deck.size(); i++) {
			std::cout << current_deck.at(i).card_id << " ";
			if(i==current_deck.size()-1) {
				std::cout << "\n";
			}
		}*/
	}
}