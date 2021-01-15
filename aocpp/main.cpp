#include <iostream>
#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"

int main()
{
	using namespace std;

	bool immediate = true;

	if (immediate) {
		day6::run();
	}
	else {
		int chosenDay = -1;
		string chosen;
		while (true) {
			cout << "Choose a day to run (1-25): ";
			cin >> chosenDay;
			cout << chosenDay << endl;

			if (chosenDay < 1 || chosenDay>25) break;

			switch (chosenDay)
			{
			case 1: day1::run(); break;
			case 2: day2::run(); break;
			case 3: day3::run(); break;
			case 4: day4::run(); break;
			case 5: day5::run(); break;
			case 6: day6::run(); break;
			default:
				cout << "not implemented yet" << endl;
				exit(1);
			}
		}
	}
}
