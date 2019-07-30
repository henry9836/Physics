#include <iostream>

#include "ConsoleController.h"
#include "menu.h"

using namespace std;

int main() {
	Banner();

	while (true){
		MainMenu();
	}

	system("pause");
	return 0;
}