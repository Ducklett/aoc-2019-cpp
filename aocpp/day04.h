#pragma once

#include <assert.h>
#include<iostream>
#include<fstream>
#include<string>

namespace day4 {

	using namespace std;

	void part1(int a, int b);
	void part2(int a, int b);

	void run() {
		ifstream t("inputs/04.txt");
		string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

		int sep = str.find('-');

		assert(sep != -1);

		auto a = stoi(str.substr(0, sep));
		auto b = stoi(str.substr(sep + 1, str.length() - sep));

		cout << str << endl;

		part1(a, b);
		part2(a, b);
	}

	void part1(int a, int b) {
		int validCount = 0;

		for (int pw = a; pw <= b; pw++) {

			bool valid = true;
			bool doubleFound = false;
			int prev = -1;

			for (int i = 100000; i >= 1; i /= 10) {
				int cur = (pw / i) % 10;

				// should never decrease
				if (prev > cur) {
					valid = false;
					break;
				}

				// should encounter double digit
				if (prev == cur) {
					doubleFound = true;
				}

				prev = cur;
			}

			valid = valid && doubleFound;

			if (valid) validCount++;
		}

		cout << "part 1: " << validCount << endl;
	}

	void part2(int a, int b) {
		int validCount = 0;

		for (int pw = a; pw <= b; pw++) {

			bool valid = true;
			bool doubleFound = false;
			int setSize = 1;
			int prev = -1;

			for (int i = 100000; i >= 1; i /= 10) {
				int cur = (pw / i) % 10;

				// should never decrease
				if (prev > cur) {
					valid = false;
					break;
				}

				// should encounter double digit
				if (prev == cur) {
					setSize++;
				}
				else {
					if (setSize == 2) {
						doubleFound = true;
					}
					setSize = 1;
				}

				prev = cur;
			}

			if (setSize == 2) doubleFound = true;

			valid = valid && doubleFound;

			if (valid) validCount++;
		}

		cout << "part 2: " << validCount << endl;
	}
}
