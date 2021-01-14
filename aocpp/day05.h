#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include <string>

namespace day5 {

	using namespace std;

	void part1(const vector<int>& numbers);
	void part2(const vector<int>& numbers);

	void run() {
		std::ifstream file("inputs/05.txt");
		std::string str;

		vector<int> numbers;
		while (std::getline(file, str)) {
			int from = 0;
			while (true) {
				bool last = false;
				int to = str.find(',', from);
				if (to == -1) {
					last = true;
					to = str.length();
				}
				int len = to - from;
				int num = stoi(str.substr(from, len));
				numbers.push_back(num);
				from = to + 1;
				if (last) break;
			}
		}

		part1(numbers);
		part2(numbers);
	}

	void part1(const vector<int>& numbers) {
		vector<int> intcode(numbers);

		const int input = 1;

		int i = 0;

		while (i < intcode.size()) {

			auto getParam = [&, i](int param) {
				int mode = (intcode[i] / (int)pow(10, param + 1)) % 10;
				return (mode == 0) ? intcode[i + param] : (i + param);
			};

			bool halt = false;
			int opcode = intcode[i] % 100;
			switch (opcode) {
			case 1: {
				intcode[getParam(3)] = intcode[getParam(1)] + intcode[getParam(2)];

				i += 4;
			} break;
			case 2: {
				intcode[getParam(3)] = intcode[getParam(1)] * intcode[getParam(2)];

				i += 4;
			} break;
			case 3: {
				int pos = getParam(1);
				intcode[pos] = input;

				i += 2;
			} break;
			case 4: {
				int v = intcode[getParam(1)];
				if (v != 0) {
					cout << "part 1: " << v << endl;
				}

				i += 2;
			} break;
			case 99: {
				halt = true;
			} break;
			default: {
				printf("Unexpected opcode %d\n", opcode);
				exit(1);
			}
			}

			if (halt) break;
		}
	}

	void part2(const vector<int>& numbers) {
		vector<int> intcode(numbers);

		const int input = 5;

		int i = 0;
		while (i < intcode.size()) {

			auto getParam = [&, i](int param) {
				int mode = (intcode[i] / (int)pow(10, param + 1)) % 10;
				return (mode == 0) ? intcode[i + param] : (i + param);
			};

			bool halt = false;
			int opcode = intcode[i] % 100;
			switch (opcode) {
			case 1: {
				intcode[getParam(3)] = intcode[getParam(1)] + intcode[getParam(2)];

				i += 4;
			} break;
			case 2: {
				intcode[getParam(3)] = intcode[getParam(1)] * intcode[getParam(2)];

				i += 4;
			} break;
			case 3: {
				int pos = getParam(1);
				intcode[pos] = input;

				i += 2;
			} break;
			case 4: {
				int v = intcode[getParam(1)];

				if (v != 0) {
					cout << "part 2: " << v << endl;
				}

				i += 2;
			} break;
			case 5: {
				int p1 = intcode[getParam(1)];
				if (p1 != 0) {
					int p2 = intcode[getParam(2)];
					i = p2;
				}
				else {
					i += 3;
				}
			} break;
			case 6: {
				int p1 = intcode[getParam(1)];
				if (p1 == 0) {
					int p2 = intcode[getParam(2)];
					i = p2;
				}
				else {
					i += 3;
				}
			} break;
			case 7: {
				int p1 = intcode[getParam(1)];
				int p2 = intcode[getParam(2)];
				int p3 = getParam(3);

				intcode[p3] = (p1 < p2) ? 1 : 0;
				i += 4;
			} break;
			case 8: {
				int p1 = intcode[getParam(1)];
				int p2 = intcode[getParam(2)];
				int p3 = getParam(3);

				intcode[p3] = (p1 == p2) ? 1 : 0;
				i += 4;
			} break;
			case 99: {
				halt = true;
			} break;
			default: {
				printf("Unexpected opcode %d\n", opcode);
				exit(1);
			}
			}

			if (halt) break;
		}
	}
}
