#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "stdafx.h"
#include "Combat.h"
#include "Country.h"

namespace Combat {
	std::string int_to_string(int i) {
		std::stringstream s;
		s << i;
		return s.str();
	}

	bool desc_order(int i, int j) { return i > j; }

	int die_roll() {
		return (rand()%6)+1;
	}

	std::vector<int> attack_roll(int num_armies) {
		int dice_roll_1;
		int dice_roll_2;
		int dice_roll_3;
		std::vector<int> attack_vector;
		if(num_armies == 1) {
			dice_roll_1 = die_roll();
			attack_vector.push_back(dice_roll_1);
		}
		else if(num_armies == 2) {
			dice_roll_1 = die_roll();
			dice_roll_2 = die_roll();
			attack_vector.push_back(dice_roll_1);
			attack_vector.push_back(dice_roll_2);
		}
		else {
			dice_roll_1 = die_roll();
			dice_roll_2 = die_roll();
			dice_roll_3 = die_roll();
			attack_vector.push_back(dice_roll_1);
			attack_vector.push_back(dice_roll_2);
			attack_vector.push_back(dice_roll_3);
		}
		std::sort(attack_vector.begin(), attack_vector.end(), desc_order);
		return attack_vector;
	}

	std::vector<int> defend_roll(int num_armies) {
		int dice_roll_1;
		int dice_roll_2;
		std::vector<int> defend_vector;
		if(num_armies == 1) {
			dice_roll_1 = die_roll();
			defend_vector.push_back(dice_roll_1);
		}
		else {
			dice_roll_1 = die_roll();
			dice_roll_2 = die_roll();
			defend_vector.push_back(dice_roll_1);
			defend_vector.push_back(dice_roll_2);
		}
		std::sort(defend_vector.begin(), defend_vector.end(), desc_order);
		return defend_vector;
	}

	std::string attack_results(std::vector<int> att) {
		std::string result;
		if(att.size() == 1) {
			result = "ATTACKER: The result of " + int_to_string(att.size()) + " dice roll is: ";
		}
		else {
			result = "ATTACKER: The results of " + int_to_string(att.size()) + " dice rolls are: ";
		}
		for(int i = 0; i < att.size(); i++) {
			result += int_to_string(att.at(i)) + " ";
		}
		return result;
	}

	std::string defend_results(std::vector<int> def) {
		std::string result;
		if(def.size() == 1) {
			result = "DEFENDER: The result of " + int_to_string(def.size()) + " dice roll is: ";
		}
		else {
			result = "DEFENDER: The results of " + int_to_string(def.size()) + " dice rolls are: ";
		}
		for(int i = 0; i < def.size(); i++) {
			result += int_to_string(def.at(i)) + " ";
		}
		return result;
	}

	int calculate_results(std::vector<int> att, std::vector<int> def) {
		//2 ==> defender loses 2
		//1 ==> defender loses 1
		//0 ==> defender and attacker lose 1
		//-1 ==> attacker loses 1
		//-2 ==> attacker loses 2
		int results = 0;
		if(att.size() > def.size()) {
			for(int i=0; i<def.size(); i++) {
				if(att.at(i) > def.at(i)) { results++;}
				else { results--;}
			}
		}
		else if(att.size() < def.size()) {
			for(int i=0; i<att.size(); i++) {
				if(att.at(i) > def.at(i)) { results++;}
				else { results--;}
			}
		}
		else {
			for(int i=0; i<att.size(); i++) {
				if(att.at(i) > def.at(i)) { results++;}
				else { results--;}
			}
		}
		return results;
	}

	std::string analyze_results(int results) {
		std::string s;
		if(results >= -1 && results <= 1) {s = "army"; }
		else { s = "armies"; }
		if(results > 0) { return "DEFENDER loses " + int_to_string(results) + " " + s; }
		else if(results < 0) { return "ATTACKER loses " + int_to_string(results*-1) + " " + s; }
		else { return "DEFENDER loses 1 " + s + " and ATTACKER loses 1 " + s; }
	}

	std::string combat_results(int num_att, int num_def, Country& att_country, Country& def_country) {
		std::string na = "ATTACKER: has commenced combat with: " + int_to_string(att_country.get_number_of_armies()) + " armies";
		std::string nd = "DEFENDER: is defending with: " + int_to_string(def_country.get_number_of_armies()) + " armies";
		std::vector<int> a = attack_roll(num_att);
		std::vector<int> d = defend_roll(num_def);
		std::string ra = attack_results(a);
		std::string rd = defend_results(d);
		int cr = calculate_results(a, d);
		std::string ar = analyze_results(cr);
		if(cr < 0) { att_country.decrement_armies(cr*(-1)); }
		else if(cr > 0) { def_country.decrement_armies(cr); }
		else { att_country.decrement_armies(1); def_country.decrement_armies(1); }
		std::string sa = int_to_string(att_country.get_number_of_armies()) + " ATTACKER armies remaining";
		std::string sd = int_to_string(def_country.get_number_of_armies()) + " DEFENDER armies remaining";
		return na + "\n" + nd + "\n" + ra + "\n" + rd + "\n" + ar + "\n" + sa + "\n" + sd + "\n";
	}

	//TODO refactor combat to only take 2 countries, and grab the data for players from a pointer in country
	void combat(Country& att_country, Country& def_country) {
		//TODO if(att_country.is_adjacent_to(def_country)) --> proceed, else --> invalid move.
		//Check if att country is owned by att player
		if(att_country.get_owner_name().compare(att_country.get_owner_name()) != 0) { 
			std::cout << att_country.get_owner_name() + " cannot attack with a country they do not own!" << std::endl;
			std::cout << att_country.get_country_name() + " is currently owned by " + att_country.get_owner_name() + "." << std::endl;
		}
		else {
			//Check if att country and def country are owned by same player
			if(att_country.get_owner_name().compare(def_country.get_owner_name()) == 0) {
				std::cout << att_country.get_owner_name() + " cannot attack their own country!" << std::endl;
			}
			else { 
				bool finished_combat = false;
				std::cout << "Combat commencing. Type 0 at any time to exit combat." << std::endl;
				while(finished_combat == false) {
					if(att_country.get_number_of_armies() > 1) {
						if(att_country.get_number_of_armies() == 2) { //roll 1 die
							bool valid_choice = false;
							int choice;
							std::cout << "ATTACKER: " + att_country.get_owner_name() + " currently has " << att_country.get_number_of_armies() << " armies in " + att_country.get_country_name() << std::endl;
							std::cout << "DEFENDER: " + def_country.get_owner_name() + " currently has " << def_country.get_number_of_armies() << " armies in " + def_country.get_country_name() << std::endl;
							while(valid_choice == false) {
								std::cout << "You can attack with 1 army." << std::endl;
								std::cout << "Please enter the number of armies you would like to attack with." << std::endl;
								std::cin >> choice;
								if(choice == 1) {
									std::cout << Combat::combat_results(1, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
									if(def_country.get_number_of_armies() == 0) {
										finished_combat = true;
										def_country.get_owner()->remove_country(def_country);
										att_country.get_owner()->assign_country(def_country);
										Combat::move_armies(choice, att_country, def_country);
									}
									valid_choice = true;
								}
								else if(choice == 0) {
									valid_choice = true;
									finished_combat = true;
								}
								else {
									std::cout << "Not a valid choice." << std::endl;
								}
							}
						}
						else if(att_country.get_number_of_armies() == 3) { //roll 1 or 2 dice
							bool valid_choice = false;
							int choice;
							std::cout << "ATTACKER: " + att_country.get_owner_name() + " currently has " << att_country.get_number_of_armies() << " armies in " + att_country.get_country_name() << std::endl;
							std::cout << "DEFENDER: " + def_country.get_owner_name() + " currently has " << def_country.get_number_of_armies() << " armies in " + def_country.get_country_name() << std::endl;
							while(valid_choice == false) {
								std::cout << "You can attack with 1 or 2 armies." << std::endl;
								std::cout << "Please enter the number of armies you would like to attack with." << std::endl;
								std::cout << "Or type 9 to go all in (automatically attack until no armies are remaining on one side or the other)" << std::endl;
								std::cin >> choice;
								if(choice == 1) {
									std::cout << Combat::combat_results(1, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
									if(def_country.get_number_of_armies() == 0) {
										finished_combat = true;
										def_country.get_owner()->remove_country(def_country);
										att_country.get_owner()->assign_country(def_country);
										Combat::move_armies(choice, att_country, def_country);
									}
									valid_choice = true;
								}
								else if(choice == 2) {
									std::cout << Combat::combat_results(2, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
									if(def_country.get_number_of_armies() == 0) {
										finished_combat = true;
										def_country.get_owner()->remove_country(def_country);
										att_country.get_owner()->assign_country(def_country);
										Combat::move_armies(choice, att_country, def_country);
									}
									valid_choice = true;
								}
								else if(choice == 9) {
									int dice_check;
									while((att_country.get_number_of_armies() > 1) && def_country.get_number_of_armies() > 0) {
										if(att_country.get_number_of_armies() > 3) {
											dice_check = 3;
										}
										else if(att_country.get_number_of_armies() == 3) {
											dice_check = 2;
										}
										else {
											dice_check = 1;
										}
										std::cout << Combat::combat_results(dice_check, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
									}
									if(def_country.get_number_of_armies() == 0) {
										finished_combat = true;
										def_country.get_owner()->remove_country(def_country);
										att_country.get_owner()->assign_country(def_country);
										Combat::move_armies(dice_check, att_country, def_country);
									}
									valid_choice = true;
								}
								else if(choice == 0) {
									valid_choice = true;
									finished_combat = true;
								}
								else {
									std::cout << "Not a valid choice." << std::endl;
								}
							}
						}
						else { //roll 1, 2 or 3 dice
							bool valid_choice = false;
							int choice;
							std::cout << "ATTACKER: " + att_country.get_owner_name() + " currently has " << att_country.get_number_of_armies() << " armies in " + att_country.get_country_name() << std::endl;
							std::cout << "DEFENDER: " + def_country.get_owner_name() + " currently has " << def_country.get_number_of_armies() << " armies in " + def_country.get_country_name() << std::endl;
							while(valid_choice == false) {
								std::cout << "You can attack with 1, 2 or 3 armies." << std::endl;
								std::cout << "Please enter the number of armies you would like to attack with." << std::endl;
								std::cout << "Or type 9 to go all in (automatically attack until no armies are remaining on one side or the other)" << std::endl;
								std::cin >> choice;
								if(choice == 1) {
									std::cout << Combat::combat_results(1, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
									if(def_country.get_number_of_armies() == 0) {
										finished_combat = true;
										def_country.get_owner()->remove_country(def_country);
										att_country.get_owner()->assign_country(def_country);
										Combat::move_armies(choice, att_country, def_country);
									}
									valid_choice = true;
								}
								else if(choice == 2) {
									std::cout << Combat::combat_results(2, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
									if(def_country.get_number_of_armies() == 0) {
										finished_combat = true;
										def_country.get_owner()->remove_country(def_country);
										att_country.get_owner()->assign_country(def_country);
										Combat::move_armies(choice, att_country, def_country);
									}
									valid_choice = true;
								}
								else if(choice == 3) {
									std::cout << Combat::combat_results(3, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
									if(def_country.get_number_of_armies() == 0) {
										finished_combat = true;
										def_country.get_owner()->remove_country(def_country);
										att_country.get_owner()->assign_country(def_country);
										Combat::move_armies(choice, att_country, def_country);
									}
									valid_choice = true;
								}
								else if(choice == 9) {
									int dice_check;
									while((att_country.get_number_of_armies() > 1) && def_country.get_number_of_armies() > 0) {
										if(att_country.get_number_of_armies() > 3) {
											dice_check = 3;
										}
										else if(att_country.get_number_of_armies() == 3) {
											dice_check = 2;
										}
										else {
											dice_check = 1;
										}
										std::cout << Combat::combat_results(dice_check, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
									}
									if(def_country.get_number_of_armies() == 0) {
										finished_combat = true;
										def_country.get_owner()->remove_country(def_country);
										att_country.get_owner()->assign_country(def_country);
										Combat::move_armies(dice_check, att_country, def_country);
									}
									valid_choice = true;
								}
								else if(choice == 0) {
									valid_choice = true;
									finished_combat = true;
								}
								else {
									std::cout << "Not a valid choice." << std::endl;
								}
							}
						}
					}
					else { 
						std::cout << att_country.get_owner_name() + " cannot attack with a country that has less than two armies!" << std::endl; 
						finished_combat = true;
					}
				}
			}
		}
	}

	void move_armies(int dice_rolled, Country& att_country, Country& def_country) {
		int moving_army_choice;
		bool valid_moving_army_choice = false;
		std::cout << "Congratulations! No defending armies remaining. Please type the number of armies you'd like to move to your new country." << std::endl;
		while(valid_moving_army_choice == false) {
			std::cout << "Any value between: " << dice_rolled << "-" << att_country.get_number_of_armies()-1 << std::endl;
			std::cin >> moving_army_choice;
			if((dice_rolled <= moving_army_choice) && (moving_army_choice <= att_country.get_number_of_armies()-1)) {
				att_country.decrement_armies(moving_army_choice);
				def_country.increment_armies(moving_army_choice);
				valid_moving_army_choice = true;
			}
		}
	}
}