#include "Graphics.h"
#include "menu.h"

void MainMenu(int argc, char** argv) {
	Console_Clear();
	string input = "";
	wcout << L" ░▒▓ Physics Main Menu ▓▒░\n ~ Henry Oliver\n\n[Options]\n 1. Lagrange's Formula\n 2. Plane vs Point Function\n 3. Line Segment vs Plane Function\n 4. Triangle vs Plane Function\n 5. Triangle Cutter\n 99. Exit\nPlease Select An Option: " << endl;
	cin >> input;
	if (input == "1") {
		LagrangeSolver();
	}
	else if (input == "2") {
		PVP();
	}
	else if (input == "3") {
		LSvPF();
	}
	else if (input == "4") {
		TvPF();
	}
	else if (input == "5") {
		InitGL(argc, argv);
	}
	else if (input == "99") {
		exit(0);
	}
	else {
		Console_OutputLog(L"Option does not exist.\n", LOGWARN);
	}
	system("pause");
}