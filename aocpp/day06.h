#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

namespace day6 {

	using namespace std;

	void part1(const unordered_map<string, string>& orbits);
	void part2(const unordered_map<string, string>& orbits);

	void run() {
		ifstream file("inputs/06.txt");
		string str;

		unordered_map<string, string> orbits;

		while (getline(file, str)) {
			auto sep = str.find(')');
			string a = str.substr(0, sep);
			string b = str.substr(sep + 1, str.length() - sep);
			orbits.insert({ b, a });
		}

		part1(orbits);
		part2(orbits);
	}

	int countOrbits(const unordered_map<string, string>& orbits, const string& obj) {
		auto parent = orbits.find(obj);
		if (parent == orbits.end()) return 0;
		return 1 + countOrbits(orbits, parent->second);
	}

	void part1(const unordered_map<string, string>& orbits) {

		int totalOrbits = 0;

		for (auto& ab : orbits) {
			totalOrbits += countOrbits(orbits, ab.first);
		}

		cout << "part 1: " << totalOrbits << endl;
	}

	void part2(const unordered_map<string, string>& orbits) {

		unordered_map<string, int> santaDist;

		auto santasOrbit = orbits.find("SAN");
		int i = 0;
		while (santasOrbit != orbits.end()) {
			santaDist.insert({ santasOrbit->second, i++ });
			santasOrbit = orbits.find(santasOrbit->second);
		}

		auto yourOrbit = orbits.find("YOU");
		i = 0;

		int distanceToSanta;
		while (yourOrbit != orbits.end()) {
			auto santa = santaDist.find(yourOrbit->second);
			if (santa != santaDist.end()) {
				distanceToSanta = i + santa->second;
				break;
			}
			yourOrbit = orbits.find(yourOrbit->second);
			i++;
		}

		cout << "part 2: " << distanceToSanta << endl;
	}
}
