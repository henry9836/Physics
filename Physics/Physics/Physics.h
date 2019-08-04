#pragma once
#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

float dotproduct(vector<float> VECA, vector<float> VECB);

vector<float> Xproduct(vector<float> VECA, vector<float> VECB);

vector<float> mutiplay(float times, vector<float> OG);

vector<float> vsubtract(vector<float> first, vector<float> second);

void TvPF();

void LSvPF();

void PVP();
