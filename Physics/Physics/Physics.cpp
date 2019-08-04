#include "Physics.h"


float dotproduct(vector<float> VECA, vector<float> VECB)
{
	float product = 0;
	for (int i = 0; i < 3; i++)
	{
		product += VECA.at(i) * VECB.at(i);
	}
	return (product);
}

vector<float> Xproduct(vector<float> VECA, vector<float> VECB)
{
	vector<float> product = { 0, 0, 0 };

	product.at(0) = VECA.at(1) * VECB.at(2) - VECA.at(2) * VECB.at(1);
	product.at(1) = VECA.at(2) * VECB.at(0) - VECA.at(0) * VECB.at(2);
	product.at(2) = VECA.at(0) * VECB.at(1) - VECA.at(1) * VECB.at(0);

	return(product);
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

vector<float> vsubtract(vector<float> first, vector<float> second)
{
	for (int i = 0; i < 3; i++)
	{
		first.at(i) = first.at(i) - second.at(i);
	}
	return(first);
}

void TvPF()
{
	vector<float>planeNormal{ 1, 0, 0 };
	vector<float>planePos{ 0, 1, 0 };
	vector<float>T0{ 2,0,0, };
	vector<float>T1{ -1,0,0 };
	vector<float>T2{ -1,1,0 };
	float ans1 = dotproduct(planeNormal, vsubtract(planePos, T0)) / dotproduct(planeNormal, vsubtract(T1, T0));
	float ans2 = dotproduct(planeNormal, vsubtract(planePos, T1)) / dotproduct(planeNormal, vsubtract(T2, T1));
	float ans3 = dotproduct(planeNormal, vsubtract(planePos, T2)) / dotproduct(planeNormal, vsubtract(T0, T2));
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
	vector<float>planeNormal{ 1, 0, 0 };
	vector<float>planePos{ 0, 1, 0 };

	vector<float>P0{ 2,0,0 };
	vector<float>P1{ -1,0,0 };

	ans = dotproduct(planeNormal, vsubtract(planePos, P0)) / dotproduct(planeNormal, vsubtract(P1, P0));

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
	vector<float>planeNormal{ 1, 0, 0 };
	vector<float>planePos{ 0, 1, 0 };
	vector<float>pointPos{ Xpos, 1, 1 };

	distance = dotproduct(planeNormal, planePos);
	ans = dotproduct(planeNormal, pointPos) - distance;
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