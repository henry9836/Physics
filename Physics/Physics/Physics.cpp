#include "Physics.h"

float dotproduct(Vector3 VECA, Vector3 VECB)
{
	float product = 0;
	product += VECA.x * VECB.x;
	product += VECA.y * VECB.y;
	product += VECA.z * VECB.z;
	return (product);
}

vector<float> mutiplay(float times, vector<float> OG)
{
	vector<float>ans = { 0,0,0 };

	for (int i = 0; i < 3; i++)
	{
		ans.at(i) = OG.at(i) * times;
	}
	return (ans);
}

Vector3 vsubtract(Vector3 first, Vector3 second)
{
	first.x = first.x - second.x;
	first.y = first.y - second.y;
	first.z = first.z - second.z;
	return(first);
}

void TrianglePlaneFunction(Vector3 plane, Vector3 planeNormal, TriangleData Triangle)
{
	//vector<float>planeNormal{ 1, 0, 0 };
	//vector<float>planePos{ 0, 1, 0 };
	//vector<float>T0{ 2,0,0, };
	//vector<float>T1{ -1,0,0 };
	//vector<float>T2{ -1,1,0 };

	//float ans1 = dotproduct(planeNormal, vsubtract(planePos, T0)) / dotproduct(planeNormal, vsubtract(T1, T0));
	//float ans2 = dotproduct(planeNormal, vsubtract(planePos, T1)) / dotproduct(planeNormal, vsubtract(T2, T1));
	//float ans3 = dotproduct(planeNormal, vsubtract(planePos, T2)) / dotproduct(planeNormal, vsubtract(T0, T2));

	float ans1 = dotproduct(planeNormal, vsubtract(plane, Triangle.firstPoint)) / dotproduct(planeNormal, vsubtract(Triangle.secondPoint, Triangle.firstPoint));
	float ans2 = dotproduct(planeNormal, vsubtract(plane, Triangle.secondPoint)) / dotproduct(planeNormal, vsubtract(Triangle.thirdPoint, Triangle.secondPoint));
	float ans3 = dotproduct(planeNormal, vsubtract(plane, Triangle.thirdPoint)) / dotproduct(planeNormal, vsubtract(Triangle.firstPoint, Triangle.thirdPoint));
	vector<float>anspool{ ans1, ans2, ans3 };

	bool ans = false;
	for (int i = 0; i < 3; i++)
	{
		if (anspool.at(i) == 0)
		{
			ans = true;
		}
		if (anspool.at(i) == 1)
		{
			ans = true;
		}
		if (anspool.at(i) < 1 && anspool.at(i) > 0)
		{
			ans = true;
		}
	}

	if (ans == true)
	{
		wcout << L"Collision is true" << endl;
	}
	else
	{
		wcout << L"Collision if false" << endl;
	}
	system("pause");
}


void LSvPF()
{

	float ans = 0;
	Vector3 planeNormal = {0,0,0};
	Vector3 planePosition = {0,0,0};

	Vector3 P0 = {0,0,0};
	Vector3 P1 = {0,0,0};

	ans = dotproduct(planeNormal, vsubtract(planePosition, P0)) / dotproduct(planeNormal, vsubtract(P1, P0));

	if (ans == 0)
	{
		wcout << L"intersection at first point" << endl;
	}
	if (ans == 1)
	{
		wcout << L"intersecion at second point" << endl;
	}
	if (ans < 0)
	{
		wcout << L"intersectoin before first point" << endl;
	}
	if (ans > 1)
	{
		wcout << L"intersection beyond second point" << endl;
	}
	if (ans < 1 && ans > 0)
	{
		wcout << L"intersection between the 2 points" << endl;
	}
	system("pause");

}

void PVP()
{
	wcout << L"what X position would you like " << endl;
	wcout << L"(0 is on -1 is benind and 1 is infront)" << endl;
	float Xpos;
	cin >> Xpos;

	float ans = 0;
	float distance = 0;

	Vector3 planeNormal = {0,0,0};
	Vector3 planePosition = { 0,0,0 };
	Vector3 pointPosition = { 0,0,0 };

	distance = dotproduct(planeNormal, planePosition);
	ans = dotproduct(planeNormal, pointPosition) - distance;
	if (ans == 0)
	{
		wcout << L"ON_PLANE" << endl;
	}
	else if (ans < 0)
	{
		wcout << L"BEHIND" << endl;
	}
	else if (ans > 0)
	{
		wcout << L"INFRONT" << endl;
	}
	system("pause");
}