#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

//ITS FOR ONLY SPEEDTEST
std::unordered_map <std::string, std::unordered_set<std::string>> all_libraries;
std::unordered_set <std::string> first_line;
std::unordered_set <std::string> second_line;

void emplace_depenence(std::string& line) {
	//имя библы, к которой строим зависимости
	std::string lib_name;
	std::string name;

	std::istringstream ss(line);

	ss >> lib_name;

	while (ss >> name) {
		all_libraries[lib_name].emplace(name);
	}

}

void emplace_depenence_reverse(std::string& line) {
	//имя библы, к которой строим зависимости
	std::string lib_name;
	std::string name;

	std::istringstream ss(line);

	ss >> lib_name;

	while (ss >> name) {
		all_libraries[name].emplace(lib_name);
	}

}

void emplace_line_in_map(const std::string& line, std::unordered_set<std::string>& set) {

	std::istringstream ss(line);
	std::string name;

	while (ss >> name) {
		all_libraries.emplace(name, std::unordered_set<std::string>());
	}
}

void emplace_line_in_set(const std::string& line, std::unordered_set<std::string>& set) {
	std::istringstream ss(line);
	std::string name;
	while (ss >> name) {
		set.emplace(name);
	}
}


void print_path_reverse(const std::string& l, std::string& path, std::unordered_set<std::string>& visited_path) {
	for (auto dep : all_libraries[l])
	{
		if (visited_path.find(dep) == visited_path.end()) {
			//path += " " + (dep);
			path.insert(0, dep + " ");
			visited_path.emplace(dep);
			//если вершина уязвима, выводим на экран
			if (second_line.find(dep) != second_line.end()) {
				//std::cout<<  path + "\n";
				printf("%s\n", path.c_str());

			}
			print_path_reverse(dep, path, visited_path);
			path.erase(0, path.find(' ') + 1);
			//path.erase(path.rfind(' '));
			visited_path.erase(dep);
		}
	}
}

void print_path(const std::string& l, std::string& path, std::unordered_set<std::string>& visited_path) {

	for (auto dep : all_libraries[l]){
		if (visited_path.find(dep) == visited_path.end()) {
			path += " " + (dep);
			visited_path.emplace(dep);
			//если вершина уязвима, выводим на экран
			if (first_line.find(dep) != first_line.end()) {
				//std::cout<<  path + "\n";
				printf("%s\n", path.c_str());
			}
			print_path(dep, path, visited_path);
			path.erase(path.rfind(' '));
			visited_path.erase(dep);
		}
	}
}

int main() {
	std::string line;

	std::getline(std::cin, line);
	emplace_line_in_set(line, first_line);
	emplace_line_in_map(line, first_line);

	std::getline(std::cin, line);
	emplace_line_in_set(line, second_line);
	emplace_line_in_map(line, first_line);


	if (second_line.size() < first_line.size()) {
		while (std::getline(std::cin, line)) {
			emplace_depenence(line);
		}
		if (all_libraries.empty()) {
			return 0;
		}
		for (auto lib : second_line) {
			if (first_line.find(lib) != first_line.end()) {
				//std::cout << lib + "\n";
				printf("%s\n", lib.c_str());
			}
			std::unordered_set <std::string> visited_path;
			visited_path.emplace(lib);
			std::string path = lib;
			print_path(lib, path, visited_path);
		}
	}
	else {
		while (std::getline(std::cin, line)) {
			emplace_depenence_reverse(line);
		}
		if (all_libraries.empty()) {
			return 0;
		}

		for (auto lib : first_line) {
			if (second_line.find(lib) != second_line.end()) {
				//std::cout << lib + "\n";
				printf("%s\n", lib.c_str());
			}
			std::unordered_set <std::string> visited_path;
			visited_path.emplace(lib);
			std::string path = lib;
			print_path_reverse(lib, path, visited_path);
		}
	}

}