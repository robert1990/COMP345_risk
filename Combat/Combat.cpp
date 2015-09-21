#include <iostream>
#include <time.h>
#include <random>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;

string intToString(int i) {
	stringstream s;
	s << i;
	return s.str();
}

bool descOrder(int i, int j) { return i > j; }

int dieRoll() {
	
	return (rand()%6)+1;
}

vector<int> attackRoll(int numArmies) {
	int dice_roll_1;
	int dice_roll_2;
	int dice_roll_3;
	vector<int> attackVector;
	if(numArmies == 1) {
		dice_roll_1 = dieRoll();
		attackVector.push_back(dice_roll_1);
	}
	else if(numArmies == 2) {
		dice_roll_1 = dieRoll();
		dice_roll_2 = dieRoll();
		attackVector.push_back(dice_roll_1);
		attackVector.push_back(dice_roll_2);
	}
	else {
		dice_roll_1 = dieRoll();
		dice_roll_2 = dieRoll();
		dice_roll_3 = dieRoll();
		attackVector.push_back(dice_roll_1);
		attackVector.push_back(dice_roll_2);
		attackVector.push_back(dice_roll_3);
	}
	std::sort(attackVector.begin(), attackVector.end(), descOrder);
	return attackVector;
}

vector<int> defendRoll(int numArmies) {
	int dice_roll_1;
	int dice_roll_2;
	vector<int> defendVector;
	if(numArmies == 1) {
		dice_roll_1 = dieRoll();
		defendVector.push_back(dice_roll_1);
	}
	else {
		dice_roll_1 = dieRoll();
		dice_roll_2 = dieRoll();
		defendVector.push_back(dice_roll_1);
		defendVector.push_back(dice_roll_2);
	}
	std::sort(defendVector.begin(), defendVector.end(), descOrder);
	return defendVector;
}

string attackResults(vector<int> attack) {
	string result;
	if(attack.size() == 1) {
		result = "ATTACKER: The result of " + intToString(attack.size()) + " dice roll is: ";
	}
	else {
		result = "ATTACKER: The results of " + intToString(attack.size()) + " dice rolls are: ";
	}
	for(int i = 0; i < attack.size(); i++) {
		result += intToString(attack[i]) + " ";
	}
	result += "\n";
	return result;
}

string defendResults(vector<int> defend) {
	string result;
	if(defend.size() == 1) {
		result = "DEFENDER: The result of " + intToString(defend.size()) + " dice roll is: ";
	}
	else {
		result = "DEFENDER: The results of " + intToString(defend.size()) + " dice rolls are: ";
	}
	for(int i = 0; i < defend.size(); i++) {
		result += intToString(defend[i]) + " ";
	}
	result += "\n";
	return result;
}

int calculateResults(vector<int> attack, vector<int> defend) {
	//2 ==> defender loses 2
	//1 ==> defender loses 1
	//0 ==> defender and attacker lose 1
	//-1 ==> attacker loses 1
	//-2 ==> attacker loses 2
	int results = 0;
	if(attack.size() > defend.size()) {
		for(int i=0; i<defend.size(); i++) {
			if(attack[i] > defend[i]) { results++;}
			else { results--;}
		}
	}
	else if(attack.size() < defend.size()) {
		for(int i=0; i<attack.size(); i++) {
			if(attack[i] > defend[i]) { results++;}
			else { results--;}
		}
	}
	else {
		for(int i=0; i<attack.size(); i++) {
			if(attack[i] > defend[i]) { results++;}
			else { results--;}
		}
	}
	return results;
}

string analyzeResults(int results) {
	string s;
	if(results >= -1 && results <= 1) {s = "army"; }
	else { s = "armies"; }
	if(results > 0) { return "DEFENDER loses " + intToString(results) + " " + s; }
	else if(results < 0) { return "ATTACKER loses " + intToString(results*-1) + " " + s; }
	else { return "DEFENDER loses 1 " + s + " and ATTACKER loses 1 " + s; }
}

string combatResults(int numAttackers, int numDefenders) {
	vector<int> a = attackRoll(numAttackers);
	vector<int> d = defendRoll(numDefenders);
	string ra = attackResults(a);
	string rd = defendResults(d);
	string ar = analyzeResults(calculateResults(a, d));
	return ra + "\n" + rd + "\n" + ar + "\n";
}

int main() {
	srand((unsigned)time(0));
	cout << combatResults(1, 1) << endl;
	cout << combatResults(2, 2) << endl;
	cout << combatResults(3, 3) << endl;
	cout << combatResults(4, 3) << endl;
	/*cout << "Please enter a number of attackers:" << endl;
	int attackers;
	int defenders;
	std::cin >> attackers;
	cout << "Please enter a number of defenders:" << endl;
	std::cin >> defenders;
	cout << combatResults(attackers, defenders) << endl;*/
}