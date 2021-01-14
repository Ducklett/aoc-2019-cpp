#pragma once 

#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace day3 {

	using namespace std;

	struct vec2 {
		int x;
		int y;

		size_t operator()(const vec2& p) const noexcept {
			size_t hash = p.x + INT_MAX * p.y;
			return hash;
		};

		bool operator==(const vec2& other) const
		{
			return (x == other.x && y == other.y);
		}
	};

	struct Move
	{
		char direction;
		int amount;
	};


	void part1(const vector<vector<Move>> wires);
	void part2(const vector<vector<Move>> wires);

}

namespace std {
	template<> struct hash<day3::vec2>
	{
		std::size_t operator()(const day3::vec2& p) const noexcept
		{
			return p(p);
		}
	};

}

namespace day3 {
	void run() {
		std::ifstream file("inputs/03.txt");
		std::string str;

		vector<vector<Move>> wires;
		while (std::getline(file, str)) {
			int from = 0;
			vector<Move> wire;
			while (true) {
				bool end = false;
				int to = str.find(',', from);
				if (to == -1) {
					to = str.length();
					end = true;
				}
				int len = to - from;

				Move m{};
				char dir = str[from];

				m.amount = stoi(str.substr(from + 1, len));
				m.direction = dir;
				wire.push_back(m);
				from = to + 1;

				if (end) break;
			}
			wires.push_back(wire);
		}

		part1(wires);
		part2(wires);
	}

	void step(vec2& pos, char direction) {
		switch (direction) {
		case 'U':pos.y += 1;  break;
		case 'D':pos.y -= 1;  break;
		case 'L':pos.x -= 1;  break;
		case 'R':pos.x += 1;  break;
		}
	}

	void part1(const vector<vector<Move>> wires) {

		std::unordered_set<vec2> visited;

		// fill set
		vec2 pos = { 0,0 };
		for (auto m : wires[0]) {
			for (int i = 0; i < m.amount; i++) {
				step(pos, m.direction);
				visited.insert(pos);
			}
		}

		// check intersections in set
		int minIntersection = INT_MAX;
		pos = { 0,0 };
		for (auto m : wires[1]) {
			for (int i = 0; i < m.amount; i++) {
				step(pos, m.direction);

				auto found = visited.find(pos);
				if (found != visited.end()) {
					// intersected
					int dist = abs(pos.x) + abs(pos.y);
					minIntersection = min(dist, minIntersection);
				}
			}
		}

		cout << "part 1: " << minIntersection << endl;
	}

	void part2(const vector<vector<Move>> wires) {
		std::unordered_map<vec2, int> visited;

		// fill costs for wire 1
		vec2 pos = { 0,0 };
		int cost = 0;
		for (auto m : wires[0]) {
			for (int i = 0; i < m.amount; i++) {
				step(pos, m.direction);

				auto found = visited.find(pos);
				if (found == visited.end()) {
					visited.insert({ pos, ++cost });
				}
			}
		}

		int minCost = INT_MAX;

		pos = { 0,0 };
		cost = 0;
		for (auto m : wires[1]) {
			for (int i = 0; i < m.amount; i++) {
				step(pos, m.direction);

				cost++;
				auto found = visited.find(pos);

				// bizzare red herring complexity going on in the text
				// don't actually need to do anything to your step count....

				if (found != visited.end()) {
					minCost = min(minCost, cost + found->second);
				}
			}
		}

		cout << "part 2: " << minCost << endl;
	}
}
