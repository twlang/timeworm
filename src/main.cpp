#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char** argv){
	if (argc == 1)
		std::cout << "Usage: " << argv[0] << " example_file.tw"

	std::ifstream file(argv[1]);
	std::string current_line
	std::string next_line;
	
	int scope = 0;

	while (std::getline(file, current_line, ';')){
		for (char c : current_line){

		}
	}
}
