#include <iostream>
#include <string>

#include "Country.h"

Country::Country(std::string name) {
	country_name = name;
	is_owned = false;
	std::cout << get_country_name() + " Country object created." << std::endl;
}

Country::~Country() {
	std::cout << get_country_name() + " Country object destroyed." << std::endl;
}

std::string Country::get_country_name() {
	return country_name;
}

bool Country::owned() {
	return is_owned;
}

void Country::set_owned(bool value) {
	is_owned = value;
}