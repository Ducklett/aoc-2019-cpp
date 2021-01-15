#pragma once

#include<iostream>
#include<fstream>
#include <vector>
#include <string>

namespace day2 {

	using namespace std;

	void part1(const vector<int>& numbers);
	void part2(const vector<int>& numbers);

	void run() {
		std::ifstream file("inputs/02.txt");
		std::string str;

		vector<int> numbers;
		while (std::getline(file, str)) {
			int from = 0;
			while (true) {
				int to = str.find(',', from);
				if (to == -1) break;
				int len = to - from;
				int num = stoi(str.substr(from, len));
				numbers.push_back(num);
				from = to + 1;
			}
		}

		part1(numbers);
		part2(numbers);
	}

	void part1(const vector<int>& numbers) {
		vector<int> intcode(numbers);

		intcode[1] = 12;
		intcode[2] = 2;

		for (int i = 0; i < intcode.size(); i += 4) {
			bool halt = false;
			int opcode = intcode[i];
			switch (opcode) {
			case 1: {
				int n1 = intcode[i + 1];
				int n2 = intcode[i + 2];
				int dest = intcode[i + 3];
				intcode[dest] = intcode[n1] + intcode[n2];
			} break;
			case 2: {
				int n1 = intcode[i + 1];
				int n2 = intcode[i + 2];
				int dest = intcode[i + 3];
				intcode[dest] = intcode[n1] * intcode[n2];
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

		cout << "part 1: " << intcode[0] << endl;
	}

	void part2(const vector<int>& numbers) {

		int target = 19690720;

		for (int noun = 0; noun < 100; noun++) {
			for (int verb = 0; verb < 100; verb++) {

				vector<int> intcode(numbers);

				intcode[1] = noun;
				intcode[2] = verb;

				for (int i = 0; i < intcode.size(); i += 4) {
					bool halt = false;
					int opcode = intcode[i];
					switch (opcode) {
					case 1: {
						int n1 = intcode[i + 1];
						int n2 = intcode[i + 2];
						int dest = intcode[i + 3];
						intcode[dest] = intcode[n1] + intcode[n2];
					} break;
					case 2: {
						int n1 = intcode[i + 1];
						int n2 = intcode[i + 2];
						int dest = intcode[i + 3];
						intcode[dest] = intcode[n1] * intcode[n2];
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

				if (intcode[0] == target) {
					cout << "part 2: " << 100 * noun + verb << endl;
					break;
				}
			}
		}
	}
}
