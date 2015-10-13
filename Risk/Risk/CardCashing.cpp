#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "stdafx.h"
#include "CardCashing.h"

/*
CARDCASHING NAMESPACE
NOTE: The CardCashing namespace is a collection of functions to do with the logic of cashing cards received by acquiring countries.
	  All functions are used within the Player's cash_cards function.
	  The goal of this namespace is to try to keep the card logic separate from the player logic.
	  For now, the only unique aspect of each card is its ID.
	  condition1 is the cashing condition where a player has 3 of the same card ID.
	  condition2 is the cashing condition where a player has 1 of each of the 3 unique IDs.
Functions:
count_ids(hand):
	A function that assesses the current state of the player's hand and returns a vector.
	This vector contains the number of 0 IDs, followed by the number of 1 IDs, and finally the number of 2 IDs.
assess_where_true(hand)
	A function that assesses the current state of the player's hand and returns a vector.
	This vector tests for condition1. Using the logic from count_ids, it assesses where the number of IDs are greater than 2.
	For example, given a hand containing three 0's, one 1, and one 1, it will return <true,false,false>.
test_condition1(hand)
	A function that assesses the current state of the player's hand and returns a bool.
	If the player's hand currently contains any of the 3 or more same IDs, it will return true.
	For example, <1,1,3> -> true, <3,0,3> -> true, <1,1,1> -> false
test_condition2(hand)
	A function that assesses the current state of the player's hand and returns a bool.
	If the player's hand currently contains at least 1 of each unique ID, it will return true.
	For example, <1,1,2> -> true, <3,2,2> -> true, <0,4,4> -> false
cash_on_condition1(hand, deck)
	A function that cashes cards from the player's hand based on condition1.
cash_on_condition2(hand, deck)
	A function that cashes cards from the player's hand based on condition2.
int condition_choice()
	A function that will be used when both condition1 and condition2 are evaluated as true.
	The int returned will correspond to the player choosing either 1 for condition1, or 2 for condition2.
*/

namespace CardCashing {
	std::vector<int> count_ids(std::vector<Deck::Card>& hand) {
		int num_zero = 0; int num_one = 0; int num_two = 0;
		for(unsigned int i=0; i<hand.size(); i++) {
			int value = hand.at(i).card_id;
			//If the value is equal to zero, increment num_zero
			if(value == 0) { num_zero++; }
			//Else if the value is equal to one, increment num_one
			else if(value == 1) { num_one++; }
			//Else, the value must be equal to two, therefore increment num_two
			else { num_two++; }
		}
		std::vector<int> result;
		result.push_back(num_zero); result.push_back(num_one); result.push_back(num_two); 
		return result;
	}

	std::vector<bool> assess_where_true(std::vector<Deck::Card>& hand) {
		//Sum the number of each ID using count_ids
		std::vector<int> amt_ids = count_ids(hand);
		std::vector<bool> true_ids;
		//Push the bool value based on an evaluation of whether the ID appears more than 2 times.
		true_ids.push_back(amt_ids[0]>2); true_ids.push_back(amt_ids[1]>2); true_ids.push_back(amt_ids[2]>2);
		return true_ids;
	}

	bool test_condition1(std::vector<Deck::Card>& hand) {
		std::vector<int> amt_ids = count_ids(hand);
		//If any of the IDs appears 3 or more times, return true.
		if((amt_ids.at(0)>2) || (amt_ids.at(1)>2) || (amt_ids.at(2)>2)) { return true; }
		//Else return false as no ID appears 3 or more times.
		else { return false; }
	}

	bool test_condition2(std::vector<Deck::Card>& hand) {
		std::vector<int> amt_ids = count_ids(hand);
		//If all IDs appear 1 or more times, return true.
		if((amt_ids.at(0)>0) && (amt_ids.at(1)>0) && (amt_ids.at(2)>0)) { return true; }
		//Else, return false as not all IDs appear.
		else { return false; }
	}

	void cash_on_condition1(std::vector<Deck::Card>& hand, Deck& deck) {
		std::vector<int> amt_ids = count_ids(hand);
		std::vector<bool> true_ids = assess_where_true(hand);
		//count tracks the number of ways the player can cash 3 or more cards.
		//For example, <3,0,3> has two ways the player can cash on. Namely with ID 0 and ID 2.
		int count = 0;
		//Based on the true_ids vector evaluated from the assess_where_true function, we can gather the value of the indices where they are true.
		//This will help check what ID(s) the player can cash on.
		//For example, <3,0,3> would evaluate to <0,2>, indicating that the condition is true for IDs 0 and 2.
		std::vector<int> indices_where_true;
		for(unsigned int i=0; i<true_ids.size(); i++) {
			//If the value at i is true, then push the i value.
			//Also increment count because there is a way the player can cash in.
			if(true_ids[i] == true) { 
				indices_where_true.push_back(i);
				count++; 
			}
		}
		//If count is equal to one, there is only one possible way to cash in.
		if(count == 1) {
			//There will be only one value pushed into indices_where_true, so it is safe to just grab the value at index 0.
			int id_to_cash = indices_where_true[0];
			for(int i=0; i<3; i++) {
				/*
				This may just be a temporary solution.
				We're pseudo returning the cards to the deck by making 3 copies of the card with the ID we're cashing.
				Making the hand vector into a vector of pointers to card would probably solve this problem.
				*/
				Deck::Card card;
				card.card_id = id_to_cash;
				deck.return_card(card);
			}
			//Initializing cash_count to 3 will begin a countdown of the number of cards left to cash in.
			int cash_count = 3;
			//While there are still cards to cash, continue looping.
			while(cash_count > 0) {
				//found indicates if a card was found yet in this loop.
				bool found = false;
				for(unsigned int i=0; i<hand.size(); i++) {
					//If an instance is found of the ID the player is cashing on, and there has not been a card found yet in this loop, then we can erase it from hand.
					if(hand.at(i).card_id == id_to_cash && found == false) {
						found = true;
						hand.erase(hand.begin()+i);
					}
				}
				//Decrement cash_count as the player has cashed in a card.
				cash_count--;
			}
		} //End of if(count == 1)
		//Else, there is more than one way of cashing in 3 of the same cards.
		else {
			std::cout << "More than one set of 3 of the same cards. Please choose the ones you'd like to cash in." << std::endl;
			for(unsigned int i=0; i<indices_where_true.size(); i++) {
				//Print choices to cash upon.
				//For example: 1. for 3 cards of ID: 2
				std::cout << i+1 << ". for 3 cards of ID: " << indices_where_true.at(i) << std::endl;
			}
			bool valid_choice = false;
			//ID to cash in will be chosen based on player's input as there are more than one way of cashing.
			int id_to_cash;
			while(valid_choice == false) {
				int choice;
				std::cin >> choice;
				//If the choice is within a valid range (1-3), take the choice-1 and set the id_to_cash as the choice.
				if((choice-1 < indices_where_true.size()) && (choice-1 >= 0)) {
					id_to_cash = choice-1;
					valid_choice = true;
				}
				//Else, the choice not valid, and the loop will begin again as valid_choice is still set to false;
				else { std::cout << "Not a valid choice." << std::endl; }
			}
			for(int i=0; i<3; i++) {
				/*
				This may just be a temporary solution.
				We're pseudo returning the cards to the deck by making 3 copies of the card with the ID we're cashing.
				Making the hand vector into a vector of pointers to card would probably solve this problem.
				*/
				Deck::Card card;
				card.card_id = id_to_cash;
				deck.return_card(card);
			}
			//Initializing cash_count to 3 will begin a countdown of the number of cards left to cash in.
			int cash_count = 3;
			//While there are still cards to cash, continue looping.
			while(cash_count > 0) {
				//found indicates if a card was found yet in this loop.
				bool found = false;
				for(unsigned int i=0; i<hand.size(); i++) {
					//If an instance is found of the ID the player is cashing on, and there has not been a card found yet in this loop, then we can erase it from hand.
					if(hand.at(i).card_id == id_to_cash && found == false) {
						found = true;
						hand.erase(hand.begin()+i);
					}
				}
				//Decrement cash_count as the player has cashed in a card.
				cash_count--;
			}
		} //End of else(count != 1)
	}

	void cash_on_condition2(std::vector<Deck::Card>& hand, Deck& deck) {
		/*
		This may just be a temporary solution.
		We're pseudo returning the cards to the deck by making 3 cards with IDs 0 to 2.
		Making the hand vector into a vector of pointers to card would probably solve this problem.
		*/
		for(int i=0; i<3; i++) {
			Deck::Card card;
			card.card_id = i;
			deck.return_card(card);
		}
		//Initializing cash_count to 0 will begin the search for the first instance of card ID equal to 0.
		int cash_count = 0;
		//While there are still cards to cash, continue looping.
		while(cash_count < 3) {
			//found indicates if a card was found yet in this loop.
			bool found = false;
			for(unsigned int i=0; i<hand.size(); i++) {
				//If an instance is found of an ID that is still left to cash, and there has not been a card found yet in this loop, then we can erase it from hand.
				//For example, if cash_count is equal to 0, the first instance of 0 is found then deleted. cash_count is then incremented, and it will find the first instance of 1.
				if(hand.at(i).card_id == cash_count && found == false) {
					found = true;
					hand.erase(hand.begin()+i);
				}
			}
			//Increment cash_count as the player has cashed in a card of the previous ID and cash_count is set for the next one to search for.
			cash_count++;
		}
	}

	int condition_choice() {
		bool valid_choice = false;
		while(valid_choice == false) {
			std::cout << "Please choose which condition you would like to cash in on:" << std::endl;
			std::cout << "1. 3 of the same card" << std::endl;
			std::cout << "2. 1 of each type of card" << std::endl;
			int choice;
			std::cin >> choice;
			//If choice is equal to 1, then cash on condition1.
			if(choice == 1) {
				valid_choice = true;
				return choice;
			}
			//Else if, choice is equal to 2, then cash on condition2.
			else if(choice == 2) {
				valid_choice = true;
				return choice;
			}
			//Else, choice is not valid. Return to the beginning of the loop as valid_choice is still false;
			else { std::cout << "Not a valid choice." << std::endl; }
		} //End of while(valid_choice == false) loop
		//If the function somehow ends up here, the default choice will be condition1.
		return 1;
	}
}