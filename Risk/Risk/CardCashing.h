#ifndef CARDCASHING_H
#define CARDCASHING_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Deck.h"

namespace CardCashing {
	std::vector<int> count_ids(std::vector<Deck::Card>& hand);
	std::vector<bool> assess_where_true(std::vector<Deck::Card>& hand);
	bool test_condition1(std::vector<Deck::Card>& hand);
	bool test_condition2(std::vector<Deck::Card>& hand);
	void cash_on_condition1(std::vector<Deck::Card>& hand, Deck& deck);
	void cash_on_condition2(std::vector<Deck::Card>& hand, Deck& deck);
	int condition_choice();
}

#endif