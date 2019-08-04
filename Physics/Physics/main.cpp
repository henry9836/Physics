#include "Graphics.h"
#include <iostream>

#include "ConsoleController.h"
#include "menu.h"

using namespace std;

int main(int argc, char** argv) {
	Banner();

	while (true){
		MainMenu(argc, argv);
	}

	system("pause");
	return 0;
}