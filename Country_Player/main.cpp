#include <iostream>
#include <string>

#include "Player.h"
#include "Country.h"

int main() {
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
	return 0;
}