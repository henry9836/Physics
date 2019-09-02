#include "Graphics.h"
#include "menu.h"
#include "Util.h"

void MainMenu(int argc, char** argv) {
	Console_Clear();
	string input = "";
	wcout << L" ░▒▓ Physics Main Menu ▓▒░\n ~ Henry Oliver\n\n[Options]\n 1. Lagrange's Formula\n 2. Plane vs Point Function\n 3. Line Segment vs Plane Function\n 4. Triangle vs Plane Function\n 5. Triangle Cutter\n 6. 2D Capsule vs 2D Capsule\n 7. Javelin throw\n 8. Point in a Triangle\n 9. Point in a Triangle (Barycentric Coordinate)\n 10. SAT Collsion\n 11. Cannon Aimer\n 99. Exit\nPlease Select An Option: " << endl;
	cin >> input;
	if (input == "1") {
		LagrangeSolver();
	}
	else if (input == "2") {
		Vector3 plane = { 0,0,0 };
		Vector3 planeNormal = { 0,0,0 };
		Vector3 point = {0,0,0};
		Console_Clear();
		wcout << L" -= Plane Position =-" << endl << L"X:";
		cin >> plane.x;
		wcout << L"Y:";
		cin >> plane.y;
		wcout << L"Z:";
		cin >> plane.z;

		wcout << L" -= Plane Normal =-" << endl << L"X:";
		cin >> planeNormal.x;
		wcout << L"Y:";
		cin >> planeNormal.y;
		wcout << L"Z:";
		cin >> planeNormal.z;

		wcout << L" -= Point Position =-" << endl << L"X:";
		cin >> point.x;
		wcout << L"Y:";
		cin >> point.y;
		wcout << L"Z:";
		cin >> point.z;

		PlanevPoint(plane, planeNormal, point);
	}
	else if (input == "3") {
		Vector3 plane = { 0,0,0 };
		Vector3 planeNormal = {0,0,0};
		LineData line;
		Console_Clear();
		wcout << L" -= Plane Position =-" << endl << L"X:";
		cin >> plane.x;
		wcout << L"Y:";
		cin >> plane.y;
		wcout << L"Z:";
		cin >> plane.z;

		wcout << L" -= Plane Normal =-" << endl << L"X:";
		cin >> planeNormal.x;
		wcout << L"Y:";
		cin >> planeNormal.y;
		wcout << L"Z:";
		cin >> planeNormal.z;

		wcout << L" -= Line =-" << endl;
		wcout << L" [ First Point ] " << endl << L"X:";
		cin >> line.firstPoint.x;
		wcout << L"Y:";
		cin >> line.firstPoint.y;
		wcout << L"Z:";
		cin >> line.firstPoint.z;
		wcout << L" [ Second Point ] " << endl << L"X:";
		cin >> line.secondPoint.x;
		wcout << L"Y:";
		cin >> line.secondPoint.y;
		wcout << L"Z:";
		cin >> line.secondPoint.z;

		LinevPlane(plane, planeNormal, line);
	}
	else if (input == "4") {
		Vector3 plane;
		Vector3 planeNormal;
		TriangleData triangle;
		Console_Clear();
		wcout << L" -= Plane Position =-" << endl << L"X:";
		cin >> plane.x;
		wcout << L"Y:";
		cin >> plane.y;
		wcout << L"Z:";
		cin >> plane.z;

		wcout << L" -= Plane Normal =-" << endl << L"X:";
		cin >> planeNormal.x;
		wcout << L"Y:";
		cin >> planeNormal.y;
		wcout << L"Z:";
		cin >> planeNormal.z;

		wcout << L" -= Triangle =-" << endl;
		wcout << L" [ First Point ] " << endl << L"X:";
		cin >> triangle.firstPoint.x;
		wcout << L"Y:";
		cin >> triangle.firstPoint.y;
		wcout << L"Z:";
		cin >> triangle.firstPoint.z;
		wcout << L" [ Second Point ] " << endl << L"X:";
		cin >> triangle.secondPoint.x;
		wcout << L"Y:";
		cin >> triangle.secondPoint.y;
		wcout << L"Z:";
		cin >> triangle.secondPoint.z;
		wcout << L" [ Third Point ] " << endl << L"X:";
		cin >> triangle.thirdPoint.x;
		wcout << L"Y:";
		cin >> triangle.thirdPoint.y;
		wcout << L"Z:";
		cin >> triangle.thirdPoint.z;

		TrianglePlaneFunction(plane, planeNormal, triangle);
	}
	else if (input == "5") {
		InitGL(argc, argv, Scene::TRIANGLE);
	}
	else if (input == "6") {
		InitGL(argc, argv, Scene::CAPSULE);
	}
	else if (input == "7") {
		javelin();
	}
	else if (input == "8") {
		InitGL(argc, argv, Scene::PIT);
	}
	else if (input == "9") {
		InitGL(argc, argv, Scene::PITB);
	}
	else if (input == "10") {
		InitGL(argc, argv, Scene::SAT);
	}
	else if (input == "11") {
		cannonAimer();
	}
	else if (input == "99") {
		exit(0);
	}
	else {
		Console_OutputLog(L"Option does not exist.\n", LOGWARN);
	}
	system("pause");
}