#include <iostream>

#include "InputProcedure.h"
#include "stdafx.h"

/*
INPUTPROCEDURE NAMESPACE
NOTE: The InputProcedure namespace is a collection of functions to do with the logic of input.
	  The collection consists of several utility functions that when combined, should handle all input requirements and error handling.
	  The goal of this namespace is to try to keep the input logic separate from the logic that requires it.

Utility Functions:
integer_input_fail_procedure(), a function that fixes the state of cin when it expects an int but receives something else.
get_choice(), a function that returns an int given from the user with the use of integer_input_fail_procedure() to handle errors.
*/

namespace InputProcedure {
	//http://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
	void integer_input_fail_procedure() {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	int get_choice() {
		int choice;
		std::cin >> choice;
		//http://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if(std::cin.fail()) {
			integer_input_fail_procedure();
		}
		return choice;
	}
}