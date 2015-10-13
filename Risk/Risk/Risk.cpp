// Risk.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>

#include "stdafx.h"

void player_testing() {
	Player p1("Justin");
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	p1.view_hand(); //Possibly refactor this to return a string?
}

void country_testing() {
	Player p1("Eric");
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	
	Country c1("Canada");
	Country c2("USA");
	Country c3("Mexico");
	
	p1.assign_country(c1);
	p1.assign_country(c2);
	p1.assign_country(c3);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	
	Player p2("Amanda");
	p2.assign_country(c1);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	std::cout << p2.get_player_name() + " currently owns: " + p2.print_countries_owned() << std::endl;
	
	p2.remove_country(c1);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	std::cout << p2.get_player_name() + " currently owns: " + p2.print_countries_owned() << std::endl;
	
	p1.remove_country(c1);
	p2.assign_country(c1);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	std::cout << p2.get_player_name() + " currently owns: " + p2.print_countries_owned() << std::endl;
}

void deck_testing() {
	Player p1("Michael");
	Deck deck;
	Deck::Card card0;
	card0.card_id = 3;
	deck.return_card(card0);
	Deck::Card card1 = deck.draw_card();
	deck.return_card(card1);
	p1.view_hand();
	p1.add_to_hand(deck.draw_card());
	p1.add_to_hand(deck.draw_card());
	p1.view_hand();
}

void card_cashing_testing() {
	Player p1("Kyle");
	Deck deck;
	for(int i=0; i<10; i++) {
		p1.add_to_hand(deck.draw_card());
	}
	p1.view_hand();
	p1.cash_cards(deck);
	p1.view_hand();
}

void combat_testing() {
	std::srand(unsigned (std::time(0)));
	Player p1("Andrew");
	Player p2("Meghan");
	Country c1("Canada");
	Country c2("USA");
	p1.assign_country(c1);
	p2.assign_country(c2);
	c1.increment_armies(40);
	c2.increment_armies(30);
	Combat::combat(c1, c2);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	std::cout << p2.get_player_name() + " currently owns: " + p2.print_countries_owned() << std::endl;
	std::cout << c1.get_country_name() + " currently has " << c1.get_number_of_armies() << " armies." << std::endl;
	std::cout << c2.get_country_name() + " currently has " << c2.get_number_of_armies() << " armies." << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "PLAYER TESTING" << std::endl;
	player_testing();

	std::cout << "\nCOUNTRY TESTING" << std::endl;
	country_testing();

	std::cout << "\nDECK TESTING" << std::endl;
	deck_testing();

	std::cout << "\nCARD CASHING TESTING" << std::endl;
	card_cashing_testing();

	std::cout << "\nCOMBAT TESTING" << std::endl;
	combat_testing();
	return 0;
}

