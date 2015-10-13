#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>

class Player;

class Country {
private:
	/*Member variables*/
	std::string country_name;
	
	Player* owner;
	bool is_owned;
	
	int number_of_armies;
public:
	Country(std::string name);
	~Country();
	std::string get_country_name();
	
	void set_owned(bool value, Player& player);
	Player* get_owner();
	std::string get_owner_name();
	bool owned();
	
	void increment_armies(int amt);
	void decrement_armies(int amt);
	int get_number_of_armies();
};

#endif