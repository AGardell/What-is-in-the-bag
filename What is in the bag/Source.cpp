/*Program taken from Reddit's DailyProgrammer:
The tiles already in play are inputted as an uppercase string.
You should output the tiles that are left in the bag. The list should be in descending order of the 
quantity of each tile left in the bag. In cases where more than one letter has the same quantity remaining, 
output those letters in alphabetical order, with blank tiles at the end.
*/

#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <sstream>
#include <stack>

std::map <char, int> Scrabble = { {'E', 12}, //Initialize scrabble map with letters and amounts
								  {'A', 9},
								  {'I', 9},
								  {'O', 8},
								  {'N', 6},
								  {'R', 6},
								  {'T', 6},
								  {'L', 4},
								  {'S', 4},
								  {'U', 4},
								  {'D', 4},
								  {'G', 3},
								  {'_', 2},
								  {'B', 2},
								  {'C', 2},
								  {'M', 2},
								  {'P', 2},
								  {'F', 2},
								  {'H', 2},
								  {'V', 2},
								  {'W', 2},
								  {'Y', 2},
								  {'K', 1},
								  {'J', 1},
								  {'X', 1},
								  {'Q', 1},
								  {'Z', 1} };

std::multimap<int, char> sortedScrabble;

void removeFromTotal(const char& ch) {
	auto it = Scrabble.find(ch);

	if (it->second == 0) { //if too many of a character is trying to be removed, throw error and terminate program.
		throw 20;
	}
	else {
		it->second -= 1;
	}
}

void sortScrabble() { //sort the letters into a multimap using the count of them as the key.
	char letter;
	int count;
	
	for (auto it = Scrabble.begin(); it != Scrabble.end(); ++it) {
		letter = it->first;
		count = it->second;

		sortedScrabble.insert(std::pair<int, char>(count, letter));
	}

}

void printMap (std::multimap<int, char> board) {
	//iterate through the sorted board concatenating a stringstream to be placed in a stack for each count of letters.
	int currentTotal = -1;
	char ch;
	std::string str;
	std::stack<std::string> toPrint; //stack is used to print in descending vs. ascending order.
	std::stringstream ss;

	for (auto it = board.begin(); it != board.end(); ++it) {
		if (currentTotal < 0) { //only used for first run through map.
			currentTotal = it->first;
			ch = it->second;
			ss << currentTotal << ": " << ch;
		}
		else if (currentTotal == it->first) { //if totals match, append to string with this character.
			ch = it->second;
			ss << ", " << ch;
		}
		else { //otherwise get a new current total and begin concatenating letters on with matching totals.
			//push existing string with total into a stack to print after iterating through.
			currentTotal = it->first;
			str = ss.str();
			toPrint.push(str);
			ch = it->second;
			ss.str("");
			ss << currentTotal << ": " << ch;
		}
	}

	str = ss.str();
	toPrint.push(str);

	while (!toPrint.empty()) {
		std::cout << toPrint.top() << std::endl;
		toPrint.pop();
	}
}

int main() { //get the input and place it into a stringstream in order to inspect each character 
			 //and remove from the bag. Than place them into a multimap for sorting by count.
	std::string input;
	std::stringstream ss;
	char ch;

	std::cin >> input;

	ss << input;
	while (ss >> ch) {
		try {
			removeFromTotal(ch);
		}
		catch (int err) {
			std::cout << "Error: The letter " << ch << " has been removed too many times." << std::endl;
			return 0;
		}
	}

	sortScrabble();
	printMap(sortedScrabble);

	return 0;
}