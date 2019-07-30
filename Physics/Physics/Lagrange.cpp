#include "Lagrange.h"

//Lagrange's Formula

float dotProduct(Vector3 A, Vector3 B) {
	return ((A.x * B.x)+(A.y * B.y)+(A.z * B.z));
}

Vector3 MultiplyVecByFloat(Vector3 A, float input) {
	A.x = A.x * input;
	A.y = A.y * input;
	A.z = A.z * input;
	return A;
}

Vector3 SubtractVecByVec(Vector3 A, Vector3 B) {
	A.x = A.x - B.x;
	A.y = A.y - B.y;
	A.z = A.z - B.z;
	return A;
}

Vector3 CrossProduct(Vector3 A, Vector3 B) {
	Vector3 result;

	result.x = A.y * B.z - A.z * B.y;
	result.y = A.z * B.x - A.x * B.z;
	result.z = A.x * B.y - A.y * B.x;

	return result;
}

bool CompareVectors(Vector3 A, Vector3 B) {

	if (A.x != B.x) {
		return false;
	}
	if (A.y != B.y) {
		return false;
	}
	if (A.z != B.z) {
		return false;
	}

	return true;
}

void LagrangeSolver() {
	Vector3 A;
	Vector3 B;
	Vector3 C;

	//Used for result compare
	Vector3 RightSide;
	Vector3 LeftSide;

	Console_Clear();
	wcout << "[ Lagrange's Formula ]\n\nInput Vector Values\n = Vector 1 =\n X: ";
	
	//Get Values From User
	cin >> A.x;
	wcout << " Y: ";
	cin >> A.y;
	wcout << " Z: ";
	cin >> A.z;

	wcout << "\n = Vector 2 =\n X: ";
	cin >> B.x;
	wcout << " Y: ";
	cin >> B.y;
	wcout << " Z: ";
	cin >> B.z;

	wcout << "\n = Vector 3 =\n X: ";
	cin >> C.x;
	wcout << " Y: ";
	cin >> C.y;
	wcout << " Z: ";
	cin >> C.z;

	//Get Dot Products

	float dAC = dotProduct(A, C);
	float dAB = dotProduct(A, B);

	wcout << "Dot Product AC: " << dAC << endl;
	wcout << "Dot Product AB: " << dAB << endl;

	//Do Rest of right side of equation (A • C)B – (A • B)C 

	RightSide = SubtractVecByVec(MultiplyVecByFloat(B, dAC), MultiplyVecByFloat(C, dAB));

	//Do Left Side A x (B x C) 

	LeftSide = CrossProduct(A, CrossProduct(B, C));

	//Compare Right/Left Side

	if (CompareVectors(LeftSide, RightSide)) {
		wcout << "VECTORS ARE EQUAL" << endl;
	}
	else {
		wcout << "VECTORS ARE NOT EQUAL!" << endl;
	}

	wcout << "The Left Vector is:  { " << LeftSide.x << ", " << LeftSide.y << ", " << LeftSide.z << " }\n";
	wcout << "The Right Vector is: { " << RightSide.x << ", " << RightSide.y << ", " << RightSide.z << " }\n";

	system("pause");
}
