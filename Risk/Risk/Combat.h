#ifndef COMBAT_H
#define COMBAT_H

#include <string>
#include <vector>

#include "Country.h"
#include "Player.h"

namespace Combat {
	std::string int_to_string(int i);
	bool desc_order(int i, int j);
	int die_roll();
	std::vector<int> attack_roll(int num_armies);
	std::vector<int> defend_roll(int num_armies);
	std::string attack_results(std::vector<int> att);
	std::string defend_results(std::vector<int> def);
	int calculate_results(std::vector<int> att, std::vector<int> def);
	std::string analyze_results(int results);
	std::string combat_results(int num_att, int num_def, Country& att_country, Country& def_country);
	void combat(Country& att_country, Country& def_country);
	void move_armies(int dice_rolled, Country& att_country, Country& def_country);
}
#endif