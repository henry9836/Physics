#include "menu.h"

void MainMenu() {
	Console_Clear();
	string input = "";
	wcout << " ▉\n▉▉▉ Physics Main Menu\n ~ Henry Oliver\n\n[Options]\n 1. Lagrange's Formula\n 2. Plane vs Point Function\n 3. Line Segment vs Plane Function\n 4. Triangle vs Plane Function\n 5. Triangle Cutter\n 99. Exit\nPlease Select An Option: " << endl;
	cin >> input;
	if (input == "1") {
		LagrangeSolver();
	}
	else if (input == "99") {
		exit(0);
	}
	else {
		Console_OutputLog(L"Option does not exist.\n", LOGWARN);
	}
	system("pause");
}