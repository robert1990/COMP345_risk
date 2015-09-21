#include <iostream>

#include "Country.h"
#include "Player.h"

int main() {
	std::cout << "Creating a country named: Canada" << std::endl;
	Country c("Canada");
	std::cout << c.get_country_name() + " has been created" << std::endl;
	std::cout << "Creating a player named: Eric" << std::endl;
	Player p("Eric");
	std::cout << p.get_player_name() + " has been created" << std::endl;
	std::cout << "Setting number of armies in country: " + c.get_country_name() << std::endl;
	std::cout << "Testing of invalid value: -1" << std::endl;
	c.set_armies(-1);
	std::cout << "Current number of armies in " + c.get_country_name() + " = ";
	std::cout << c.get_number_of_armies() << std::endl;
	std::cout << "Testing of valid value: 5" << std::endl;
	c.set_armies(5);
	std::cout << "Current number of armies in " + c.get_country_name() + " = ";
	std::cout << c.get_number_of_armies() << std::endl;
	std::cout << "Incrementing the number of armies in country: " + c.get_country_name() << std::endl;
	std::cout << "Testing of invalid value: -1" << std::endl;
	c.increment_armies(-1);
	std::cout << "Current number of armies in " + c.get_country_name() + " = ";
	std::cout << c.get_number_of_armies() << std::endl;
	std::cout << "Testing of valid value: 2" << std::endl;
	c.increment_armies(2);
	std::cout << "Current number of armies in " + c.get_country_name() + " = ";
	std::cout << c.get_number_of_armies() << std::endl;
	std::cout << "Decrementing the number of armies in country: " + c.get_country_name() << std::endl;
	std::cout << "Testing of valid value: 2" << std:: endl;
	c.decrement_armies(2);
	std::cout << "Current number of armies in " + c.get_country_name() + " = ";
	std::cout << c.get_number_of_armies() << std::endl;
	std::cout << "Testing of invalid value: -1" << std::endl;
	c.decrement_armies(-1);
	std::cout << "Current number of armies in " + c.get_country_name() + " = ";
	std::cout << c.get_number_of_armies() << std::endl;
	std::cout << "Testing of invalid value: 6 (will bring the number of armies below 0)" << std::endl;
	c.decrement_armies(6);
	std::cout << "Current number of armies in " + c.get_country_name() + " = ";
	std::cout << c.get_number_of_armies() << std::endl;
	return 0;
}