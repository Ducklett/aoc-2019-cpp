#pragma once

#include<iostream>
#include<fstream>
#include <vector>
#include <string>

namespace day1 {

	using namespace std;

	void part1(const vector<int>& numbers);
	void part2(vector<int>& numbers);

	void run() {
		std::ifstream file("inputs/01.txt");
		std::string str;

		vector<int> numbers;
		while (std::getline(file, str)) {
			numbers.push_back(std::stoi(str));
		}

		part1(numbers);
		part2(numbers);
	}

	void part1(const vector<int>& numbers) {
		int res = 0;

		for (auto& num : numbers) {
			if (num <= 0) continue;
			int needed = (num / 3) - 2;
			res += needed;
		}

		std::cout << "part 1: " << res << endl;
	}

	void part2(vector<int>& numbers) {
		int res = 0;

		while (true) {
			bool resChanged = false;
			for (int i = 0; i < numbers.size(); i++) {
				int num = numbers[i];
				if (num > 0) {
					resChanged = true;
					int needed = (num / 3) - 2;
					if (needed < 0) needed = 0;
					numbers[i] = needed;
					res += needed;
				}
			}

			if (!resChanged) break;
		}

		std::cout << "part 2: " << res << endl;
	}
}
