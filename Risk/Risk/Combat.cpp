#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "stdafx.h"
#include "Combat.h"
#include "Country.h"

/*
COMBAT NAMESPACE
NOTE: The Combat namepsace is a collection of functions to do with the logic of combat between two countries.
	  The collection consists of several utility functions that when combined simulate the combat mechanic of the board game.
	  The goal of this namespace is to try to keep the combat logic separate from the country logic.

Utility Functions:
int_to_string(i), a function that simply takes an int and converts it to a string equivalent.
desc_order(i, j), a function that will be used to order the dice rolls in descending order for easier analysis.
die_roll(), a function that will simulate the roll of a 6 sided die.
attack_roll(num_armies), a function that given the number of available attacking armies, will roll the corresponding number of dice and push it to a vector.
defend_roll(num_armies), a function that given the number of defending armies, will roll the corresponding number of dice and push it to a vector which will be returned..
attack_results(att), a function that given the result of attack_roll, will store the results in string format which will be returned.
defend_results(def), a function that given the result of defend_roll, will store the results in string format which will be returned.
calculate_results(att, def), a function that given the result of attack_roll and defend_roll will return an int representing the actual calculation of the number of armies lost in battle.
analyze_results(results), a function that given the int value of calculate_results, will store the results in string format which will be returned.
combat_results(num_att, num_def, att_country, def_country), a function that uses all the previous functions to simulate one iteration of a battle, and stores the results in string format which will be returned.
****IN ADDITION, IT ALSO PERFORMS THE APPROPRIATE DECREMENTS OF ARMIES FOR LOSING COUNTRIES.****
move_armies(dice_rolled, att_country, def_country), a function used after a defending country has no armies remaining in order to move an amount of armies from the attacker's country to the defending country.

Actual Combat Function (where the magic happens):
combat(att_country, def_country), a function that given two countries will simulate the entire battle sequence.
*/

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
		//If the number of available attacking armies is equal to 1, then only roll 1 die.
		if(num_armies == 1) {
			dice_roll_1 = die_roll();
			attack_vector.push_back(dice_roll_1);
		}
		//Else if, the number of available attacking armies is equal to 2, then 2 dice are rolled.
		else if(num_armies == 2) {
			dice_roll_1 = die_roll();
			dice_roll_2 = die_roll();
			attack_vector.push_back(dice_roll_1);
			attack_vector.push_back(dice_roll_2);
		}
		//Else, the number of available attacking armies is greater than or equal to 3, and 3 dice are rolled.
		else {
			dice_roll_1 = die_roll();
			dice_roll_2 = die_roll();
			dice_roll_3 = die_roll();
			attack_vector.push_back(dice_roll_1);
			attack_vector.push_back(dice_roll_2);
			attack_vector.push_back(dice_roll_3);
		}
		//Sort the vector in descending order, so comparison is easier.
		std::sort(attack_vector.begin(), attack_vector.end(), desc_order);
		return attack_vector;
	}

	std::vector<int> defend_roll(int num_armies) {
		int dice_roll_1;
		int dice_roll_2;
		std::vector<int> defend_vector;
		//If the number of defending armies is equal to 1, then only roll 1 die.
		if(num_armies == 1) {
			dice_roll_1 = die_roll();
			defend_vector.push_back(dice_roll_1);
		}
		//Else, the number of defending armies is greater than or equal to 2, and 2 dice are rolled.
		else {
			dice_roll_1 = die_roll();
			dice_roll_2 = die_roll();
			defend_vector.push_back(dice_roll_1);
			defend_vector.push_back(dice_roll_2);
		}
		//Sort the vector in descending order, so comparison is easier.
		std::sort(defend_vector.begin(), defend_vector.end(), desc_order);
		return defend_vector;
	}

	std::string attack_results(std::vector<int> att) {
		std::string result;
		//If the number of available attackers is equal to 1, format the string appropriately.
		if(att.size() == 1) {
			result = "ATTACKER: The result of " + int_to_string(att.size()) + " dice roll is: "; //Formatting
		}
		//Else the number of available attackers is greater than or equal to 2, format the string appropriately.
		else {
			result = "ATTACKER: The results of " + int_to_string(att.size()) + " dice rolls are: "; //Formatting
		}
		for(int i = 0; i < att.size(); i++) {
			//Store the results of the attacker's dice to be returned.
			result += int_to_string(att.at(i)) + " ";
		}
		return result;
	}

	std::string defend_results(std::vector<int> def) {
		std::string result;
		//If the number of defenders is equal to 1, format the string appropriately.
		if(def.size() == 1) {
			result = "DEFENDER: The result of " + int_to_string(def.size()) + " dice roll is: "; //Formatting
		}
		//Else, the number of defenders is greater than or equal to 2, format the string appropriately.
		else {
			result = "DEFENDER: The results of " + int_to_string(def.size()) + " dice rolls are: "; //Formatting
		}
		for(int i = 0; i < def.size(); i++) {
			//Store the results of the defender's dice to be returned.
			result += int_to_string(def.at(i)) + " ";
		}
		return result;
	}

	int calculate_results(std::vector<int> att, std::vector<int> def) {
		/*
		POSSIBLE RESULTS:
		2 ==> defender loses 2
		1 ==> defender loses 1
		0 ==> defender and attacker lose 1
		-1 ==> attacker loses 1
		-2 ==> attacker loses 2
		*/

		//Initialize the results to 0, which will be incremented and decremented accordingly.
		int results = 0;
		//If the number of dice rolled by attacker is larger than that of defender, we'll only go to the end of the defender's rolls.
		if(att.size() > def.size()) {
			for(int i=0; i<def.size(); i++) {
				//If the roll for attacker is larger than defender, then increment results.
				if(att.at(i) > def.at(i)) { results++;}
				//Else, the roll of attacker must be smaller or equal, therefore decrement results.
				else { results--;}
			}
		}
		//Else if, the number of dice rolled by attacker is smaller than that of defender, we'll only go to the end of the attacker's rolls.
		else if(att.size() < def.size()) {
			for(int i=0; i<att.size(); i++) {
				//If the roll for attacker is larger than defender, then increment results.
				if(att.at(i) > def.at(i)) { results++;}
				//Else, the roll of attacker must be smaller or equal, therefore decrement results.
				else { results--;}
			}
		}
		//Else, the number of dice rolled by attacker is the same as that of the defender, so we can go to the end of either attacker or defender's rolls.
		else {
			for(int i=0; i<att.size(); i++) {
				//If the roll for attacker is larger than defender, then increment results.
				if(att.at(i) > def.at(i)) { results++;}
				//Else, the roll of attacker must be smaller or equal, therefore decrement results.
				else { results--;}
			}
		}
		return results;
	}

	std::string analyze_results(int results) {
		std::string s;
		//If the results indicate a singular army being lost, format appropriately.
		if(results >= -1 && results <= 1) {s = "army"; } //Formatting
		//Else, the results must indice more than one army being lost, therefore format appropriately.
		else { s = "armies"; } //Formatting
		//If the results are greater than 0, this indicates the defender losing armies.
		if(results > 0) { return "DEFENDER loses " + int_to_string(results) + " " + s; }
		//Else if, the results are smaller than 0, this indicates the attacker losing armies.
		else if(results < 0) { return "ATTACKER loses " + int_to_string(results*-1) + " " + s; }
		//Else, the result must be equal to 0, and this indicates a tie (attacker and defender losing armies).
		else { return "DEFENDER loses 1 " + s + " and ATTACKER loses 1 " + s; }
	}

	std::string combat_results(int num_att, int num_def, Country& att_country, Country& def_country) {
		/*
		This function is simply an accumulation of all previous functions, including one important aspect from the Country class.
		The actual decrementing of armies within the losing countries is performed within this function.
		Other than the important aspect of doing the actual decrementing, it simply returns the string representation of a single battle iteration within the battle sequence.

		Example output:
		ATTACKER: has commenced combat with: 40 armies
		DEFENDER: is defending with: 30 armies
		ATTACKER: The results of 3 dice rolls are: 5 4 4
		DEFENDER: The results of 2 dice rolls are: 6 2
		DEFENDER loses 1 army and ATTACKER loses 1 army
		39 ATTACKER armies remaining
		29 DEFENDER armies remaining
		*/
		std::string na = "ATTACKER: has commenced combat with: " + int_to_string(att_country.get_number_of_armies()) + " armies";
		std::string nd = "DEFENDER: is defending with: " + int_to_string(def_country.get_number_of_armies()) + " armies";
		std::vector<int> a = attack_roll(num_att);
		std::vector<int> d = defend_roll(num_def);
		std::string ra = attack_results(a);
		std::string rd = defend_results(d);
		int cr = calculate_results(a, d);
		std::string ar = analyze_results(cr);
		//If the results are smaller than 0, then the attacker loses armies. Decrement these armies from the country.
		if(cr < 0) { att_country.decrement_armies(cr*(-1)); }
		//Else if, the results are greater than 0, then the defender loses armies. Decrement these armies from the country.
		else if(cr > 0) { def_country.decrement_armies(cr); }
		//Else, the result must be equal to 0, then both the attacker and defender lose armies. Decrement these armies from both countries.
		else { att_country.decrement_armies(1); def_country.decrement_armies(1); }
		std::string sa = int_to_string(att_country.get_number_of_armies()) + " ATTACKER armies remaining";
		std::string sd = int_to_string(def_country.get_number_of_armies()) + " DEFENDER armies remaining";
		return na + "\n" + nd + "\n" + ra + "\n" + rd + "\n" + ar + "\n" + sa + "\n" + sd + "\n";
	}

	/*
	This function is MASSIVE. I believe I can make it quite a bit smaller with the addition of more utility functions.
	-Conquering a country when def_country has 0 armies should be made into a function.
	-Functions should be made for attack_with_one_army, attack_with_two_army and attack_with_many_army.
	*/
	void combat(Country& att_country, Country& def_country) {
		/*
		POSSIBLE INPUTS:
		1,2,3 for the number of armies the attacker wishes to attack with (if only 2 armies within country, can only roll 1 die and the option for 2 or 3 will not be available).
		9 for ALL IN, which will continue an attack until the attacker either wins, or loses using the maximum number of dice available each time.
		0 to finish the combat between att_country and def_country.
		*/

		//TODO if(att_country.is_adjacent_to(def_country)) --> proceed, else --> invalid move.
		//If att_country's owner name is the same as def_country's, inform the system that the player is attempting to attack their own country.
		if(att_country.get_owner_name().compare(def_country.get_owner_name()) == 0) {
			std::cout << att_country.get_owner_name() + " cannot attack their own country!" << std::endl;
		}
		//Else, the att_country's owner is not the same as def_country's. A valid attack move has been issued and the function can proceed.
		else { 
			//A combat sequence can last many iterations.
			//finished_combat will remain false until either the attacking player wishes to stop attacking, or one side of the battle has lost.
			bool finished_combat = false;
			//The start of the combat sequence between att_country and def_country
			std::cout << "Combat commencing. Type 0 at any time to exit combat." << std::endl;
			while(finished_combat == false) {
				//If the number of armies in att_country are equal to 2 or greater, then the the attack can proceed as it is valid.
				if(att_country.get_number_of_armies() > 1) {
					//If the number of armies in att_country is equal to 2, then the attacking player can roll only 1 die.
					if(att_country.get_number_of_armies() == 2) {
						bool valid_choice = false;
						//Only 2 possible valid choices, namely 1 for attack with 1 army, and 0 for exit combat.
						int choice;
						std::cout << "ATTACKER: " + att_country.get_owner_name() + " currently has " << att_country.get_number_of_armies() << " armies in " + att_country.get_country_name() << std::endl;
						std::cout << "DEFENDER: " + def_country.get_owner_name() + " currently has " << def_country.get_number_of_armies() << " armies in " + def_country.get_country_name() << std::endl;
						while(valid_choice == false) {
							std::cout << "You can attack with 1 army." << std::endl;
							std::cout << "Please enter the number of armies you would like to attack with." << std::endl;
							std::cin >> choice;
							//If the choice is equal to 1, the attacker has chosen to attack with their 1 army.
							if(choice == 1) {
								//Print the results/perform appropriate decrements
								std::cout << Combat::combat_results(1, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
								//If the def_country has no remaining armies, the attacking country can move armies to it.
								if(def_country.get_number_of_armies() == 0) {
									finished_combat = true;
									//Through the Player pointer in def_country, remove the def_country from their countries_owned vector
									def_country.get_owner()->remove_country(def_country);
									//Through the Player pointer in att_country, assign the def_country to their countries_owned vector
									att_country.get_owner()->assign_country(def_country);
									//Attacker uses move_armies logic to move a number of armies from att_country to def_country
									Combat::move_armies(choice, att_country, def_country);
								}
								valid_choice = true;
							}
							//Else if, choice is 0, then the attacker has chosen to exit combat.
							else if(choice == 0) {
								valid_choice = true;
								finished_combat = true;
							}
							//Else, any other choice is not valid.
							else {
								std::cout << "Not a valid choice." << std::endl;
							}
						} //End of while(valid_choice == false)
					} //End of if(att_country.get_number_of_armies() == 2)
					//Else if, the number of armies in att_country is equal to 3, then the attacking player can roll only 1 or 2 dice.
					else if(att_country.get_number_of_armies() == 3) { 
						bool valid_choice = false;
						//Only 4 possible valid choices, namely 1 for attack with 1 army, 2 for attack with 2 armies, 9 for ALL IN and 0 for exit combat.
						int choice;
						std::cout << "ATTACKER: " + att_country.get_owner_name() + " currently has " << att_country.get_number_of_armies() << " armies in " + att_country.get_country_name() << std::endl;
						std::cout << "DEFENDER: " + def_country.get_owner_name() + " currently has " << def_country.get_number_of_armies() << " armies in " + def_country.get_country_name() << std::endl;
						while(valid_choice == false) {
							std::cout << "You can attack with 1 or 2 armies." << std::endl;
							std::cout << "Please enter the number of armies you would like to attack with." << std::endl;
							std::cout << "Or type 9 to go all in (automatically attack until no armies are remaining on one side or the other)" << std::endl;
							std::cin >> choice;
							//If the choice is equal to 1, the attacker has chosen to attack with their 1 army.
							if(choice == 1) {
								//Print the results/perform appropriate decrements
								std::cout << Combat::combat_results(1, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
								//If the def_country has no remaining armies, the attacking country can move armies to it.
								if(def_country.get_number_of_armies() == 0) {
									finished_combat = true;
									//Through the Player pointer in def_country, remove the def_country from their countries_owned vector
									def_country.get_owner()->remove_country(def_country);
									//Through the Player pointer in att_country, assign the def_country to their countries_owned vector
									att_country.get_owner()->assign_country(def_country);
									//Attacker uses move_armies logic to move a number of armies from att_country to def_country
									Combat::move_armies(choice, att_country, def_country);
								}
								valid_choice = true;
							}
							//Else if, the choice is equal to 2, the attacker has chosen to attack with their 2 armies.
							else if(choice == 2) {
								//Print the results/perform appropriate decrements
								std::cout << Combat::combat_results(2, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
								//If the def_country has no remaining armies, the attacking country can move armies to it.
								if(def_country.get_number_of_armies() == 0) {
									finished_combat = true;
									//Through the Player pointer in def_country, remove the def_country from their countries_owned vector
									def_country.get_owner()->remove_country(def_country);
									//Through the Player pointer in att_country, assign the def_country to their countries_owned vector
									att_country.get_owner()->assign_country(def_country);
									//Attacker uses move_armies logic to move a number of armies from att_country to def_country
									Combat::move_armies(choice, att_country, def_country);
								}
								valid_choice = true;
							}
							//Else if, the choice is equal to 9, the attacker has chosen to ALL IN
							else if(choice == 9) {
								//Because ALL IN uses the max amount of dice each iteration, we must keep track for the case where the attacker conquers the defending country.
								//For example, if in the ALL IN sequence, the first sequence used 3 dice and the last iteration used 2 dice, then the attacker can only move 2 armies, and not the 3 it initially started with. 
								int dice_check;
								//While the number of armies in att_country is greater than 1, and the number of armies in def_country is greater than 0, continue looping.
								while((att_country.get_number_of_armies() > 1) && def_country.get_number_of_armies() > 0) {
									//If the number of armies in att_country is greater than 3, roll 3 dice.
									if(att_country.get_number_of_armies() > 3) {
										dice_check = 3;
									}
									//Else if, the number of armies in att_country is equal to 3, roll 2 dice.
									else if(att_country.get_number_of_armies() == 3) {
										dice_check = 2;
									}
									//Else, the number of armies must be equal to 2, therefore roll 1 die.
									else {
										dice_check = 1;
									}
									//Print the results/perform appropriate decrements
									std::cout << Combat::combat_results(dice_check, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
								}
								//If the def_country has no remaining armies, the attacking country can move armies to it.
								if(def_country.get_number_of_armies() == 0) {
									finished_combat = true;
									//Through the Player pointer in def_country, remove the def_country from their countries_owned vector
									def_country.get_owner()->remove_country(def_country);
									//Through the Player pointer in att_country, assign the def_country to their countries_owned vector
									att_country.get_owner()->assign_country(def_country);
									//Attacker uses move_armies logic to move a number of armies from att_country to def_country
									Combat::move_armies(dice_check, att_country, def_country);
								}
								valid_choice = true;
							} //End of else if(choice == 9)
							//Else if, choice is 0, then the attacker has chosen to exit combat.
							else if(choice == 0) {
								valid_choice = true;
								finished_combat = true;
							}
							//Else, any other choice is not valid.
							else {
								std::cout << "Not a valid choice." << std::endl;
							}
						} //End of while(valid_choice == false)
					} //End of else if(att_country.get_number_of_armies() == 3)
					//Else, the number of armies in att_country is greater than or equal to 4, then the attacking player can roll only 1, 2 or 3 dice.
					else { 
						bool valid_choice = false;
						//Only 5 possible valid choices, namely 1 for attack with 1 army, 2 for attack with 2 armies, 3 for attack with 3 armies, 9 for ALL IN and 0 for exit combat.
						int choice;
						std::cout << "ATTACKER: " + att_country.get_owner_name() + " currently has " << att_country.get_number_of_armies() << " armies in " + att_country.get_country_name() << std::endl;
						std::cout << "DEFENDER: " + def_country.get_owner_name() + " currently has " << def_country.get_number_of_armies() << " armies in " + def_country.get_country_name() << std::endl;
						while(valid_choice == false) {
							std::cout << "You can attack with 1, 2 or 3 armies." << std::endl;
							std::cout << "Please enter the number of armies you would like to attack with." << std::endl;
							std::cout << "Or type 9 to go all in (automatically attack until no armies are remaining on one side or the other)" << std::endl;
							std::cin >> choice;
							//If the choice is equal to 1, the attacker has chosen to attack with their 1 army.
							if(choice == 1) {
								//Print the results/perform appropriate decrements
								std::cout << Combat::combat_results(1, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
								//If the def_country has no remaining armies, the attacking country can move armies to it.
								if(def_country.get_number_of_armies() == 0) {
									finished_combat = true;
									//Through the Player pointer in def_country, remove the def_country from their countries_owned vector
									def_country.get_owner()->remove_country(def_country);
									//Through the Player pointer in att_country, assign the def_country to their countries_owned vector
									att_country.get_owner()->assign_country(def_country);
									//Attacker uses move_armies logic to move a number of armies from att_country to def_country
									Combat::move_armies(choice, att_country, def_country);
								}
								valid_choice = true;
							}
							//Else if, the choice is equal to 2, the attacker has chosen to attack with their 2 armies.
							else if(choice == 2) {
								//Print the results/perform appropriate decrements
								std::cout << Combat::combat_results(2, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
								//If the def_country has no remaining armies, the attacking country can move armies to it.
								if(def_country.get_number_of_armies() == 0) {
									finished_combat = true;
									//Through the Player pointer in def_country, remove the def_country from their countries_owned vector
									def_country.get_owner()->remove_country(def_country);
									//Through the Player pointer in att_country, assign the def_country to their countries_owned vector
									att_country.get_owner()->assign_country(def_country);
									//Attacker uses move_armies logic to move a number of armies from att_country to def_country
									Combat::move_armies(choice, att_country, def_country);
								}
								valid_choice = true;
							}
							//Else if, the choice is equal to 3, the attacker has chosen to attack with their 3 armies.
							else if(choice == 3) {
								//Print the results/perform appropriate decrements
								std::cout << Combat::combat_results(3, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
								//If the def_country has no remaining armies, the attacking country can move armies to it.
								if(def_country.get_number_of_armies() == 0) {
									finished_combat = true;
									//Through the Player pointer in def_country, remove the def_country from their countries_owned vector
									def_country.get_owner()->remove_country(def_country);
									//Through the Player pointer in att_country, assign the def_country to their countries_owned vector
									att_country.get_owner()->assign_country(def_country);
									//Attacker uses move_armies logic to move a number of armies from att_country to def_country
									Combat::move_armies(choice, att_country, def_country);
								}
								valid_choice = true;
							}
							//Else if, the choice is equal to 9, the attacker has chosen to ALL IN
							else if(choice == 9) {
								//Because ALL IN uses the max amount of dice each iteration, we must keep track for the case where the attacker conquers the defending country.
								//For example, if in the ALL IN sequence, the first sequence used 3 dice and the last iteration used 2 dice, then the attacker can only move 2 armies, and not the 3 it initially started with. 
								int dice_check;
								//While the number of armies in att_country is greater than 1, and the number of armies in def_country is greater than 0, continue looping.
								while((att_country.get_number_of_armies() > 1) && def_country.get_number_of_armies() > 0) {
									//If the number of armies in att_country is greater than 3, roll 3 dice.
									if(att_country.get_number_of_armies() > 3) {
										dice_check = 3;
									}
									//Else if, the number of armies in att_country is equal to 3, roll 2 dice.
									else if(att_country.get_number_of_armies() == 3) {
										dice_check = 2;
									}
									//Else, the number of armies must be equal to 2, therefore roll 1 die.
									else {
										dice_check = 1;
									}
									//Print the results/perform appropriate decrements
									std::cout << Combat::combat_results(dice_check, def_country.get_number_of_armies(), att_country, def_country) << std::endl;
								}
								//If the def_country has no remaining armies, the attacking country can move armies to it.
								if(def_country.get_number_of_armies() == 0) {
									finished_combat = true;
									//Through the Player pointer in def_country, remove the def_country from their countries_owned vector
									def_country.get_owner()->remove_country(def_country);
									//Through the Player pointer in att_country, assign the def_country to their countries_owned vector
									att_country.get_owner()->assign_country(def_country);
									//Attacker uses move_armies logic to move a number of armies from att_country to def_country
									Combat::move_armies(dice_check, att_country, def_country);
								}
								valid_choice = true;
							} //End of else if(choice == 9)
							//Else if, choice is 0, then the attacker has chosen to exit combat.
							else if(choice == 0) {
								valid_choice = true;
								finished_combat = true;
							}
							//Else, any other choice is not valid.
							else {
								std::cout << "Not a valid choice." << std::endl;
							}
						} //End of while(valid_choice == false)
					} //End of else(att_country.get_number_of_armies() > 3)
				} //End of if(att_country.get_number_of_armies() > 1)
				//Else, number of armies in the country must be equal to 1, therefore inform the system of an invalid attack.
				else { 
					std::cout << att_country.get_owner_name() + " cannot attack with a country that has less than two armies!" << std::endl; 
					//Combat can no longer continue, therefore set finished_combat to true.
					finished_combat = true;
				} 
			} //End of while(finished_combat == false)
		} //End of else(att_country.get_owner_name().compare(def_country.get_owner_name()) != 0)
	}

	void move_armies(int dice_rolled, Country& att_country, Country& def_country) {
		//moving_army_choice will be valid within the range of dice_rolled and number of armies in att_country minus one (have to leave one army behind).
		int moving_army_choice;
		bool valid_moving_army_choice = false;
		std::cout << "Congratulations! No defending armies remaining. Please type the number of armies you'd like to move to your new country." << std::endl;
		while(valid_moving_army_choice == false) {
			std::cout << "Any value between: " << dice_rolled << "-" << att_country.get_number_of_armies()-1 << std::endl;
			std::cin >> moving_army_choice;
			//if moving_army choice is within the range, then the appropriate decrements and increments can be performed.
			if((dice_rolled <= moving_army_choice) && (moving_army_choice <= att_country.get_number_of_armies()-1)) {
				att_country.decrement_armies(moving_army_choice);
				def_country.increment_armies(moving_army_choice);
				valid_moving_army_choice = true;
			}
		}
	}
}