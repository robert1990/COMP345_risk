#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>

class Player;

class Country {
private:
	std::string country_name;
	bool is_owned;
public:
	Country(std::string name);
	~Country();
	std::string get_country_name();
	void assign_owner(Player player);
	bool owned();
	void set_owned(bool value);
};

#endif