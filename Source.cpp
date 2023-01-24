#include <iostream>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <sstream>

std::unordered_set <std::string>first_line;
std::unordered_set<std::string> second_line;
std::unordered_map<std::string, std::unordered_set<std::string>> deps;
std::string result;


void split(std::istringstream& iss, std::unordered_set<std::string>& split_line) {
	split_line.clear();
	std::string temp;
	while (iss >> temp) {
		split_line.emplace(temp);
	}
}

void reverse_split(std::istringstream& iss) {
	std::string name;
	iss >> name;

	std::string temp;
	while (iss >> temp) {
		deps[temp].emplace(name);
	}
}


void travel(std::string& vertex, std::string& path, std::unordered_set<std::string>& visited_libs, bool reverse = false) {
	if (path.empty()) {
		path = vertex;
	}
	else if(!reverse){
		path += " " + vertex;
	}
	else {
		path = vertex + " " + path;
	}
	visited_libs.emplace(vertex);
	
	if (first_line.find(vertex) != first_line.end() ) {
		result += path + "\n";
	}

	auto it = deps.find(vertex);
	if (it != deps.end()) {
		auto& it_sec_ref = (*it).second;
		for (auto el : it_sec_ref) {
			if (visited_libs.find(el) == visited_libs.end()) {
				travel(el, path, visited_libs,reverse);
				visited_libs.erase(el);

				if (path.rfind(' ') != std::string::npos && !reverse) {
					path.erase(path.rfind(' '));
				}
				if (path.find(' ') != std::string::npos && reverse) {
					path.erase(0, path.find(' ') + 1);
				}
			}

		}
	}
}



int main() {

	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::string line;
	std::istringstream iss(line);

	std::getline(std::cin, line);
	iss.clear();
	iss.str(line);
	split(iss, first_line);


	std::getline(std::cin, line);
	iss.clear();
	iss.str(line);
	split(iss, second_line);

	bool reverse = false;

	if (first_line.size() >= second_line.size()) {
		std::string name;
		std::unordered_set<std::string> temp;
		while (std::getline(std::cin, line)) {
			iss.clear();
			iss.str(line);
			iss >> name;

			split(iss, temp);
			deps[name] = temp;
		}
		
	}
	else {
		while (std::getline(std::cin, line)) {
			iss.clear();
			iss.str(line);
			reverse_split(iss);
		}
		std::swap(first_line, second_line);
		reverse = true;
	}

	std::string path;
	std::unordered_set<std::string> visited_libs;
	for (auto el : second_line)
	{
		path.clear();
		visited_libs.clear();
		travel(el, path, visited_libs,reverse);
	}
	printf("%s", result.c_str());
}