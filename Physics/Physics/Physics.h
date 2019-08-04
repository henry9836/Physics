#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include "Util.h"

using namespace std;

float dotproduct(Vector3 VECA, Vector3 VECB);

vector<float> mutiplay(float times, vector<float> OG);

Vector3 vsubtract(Vector3 first, Vector3 second);

void TrianglePlaneFunction(Vector3 plane, Vector3 planeNormal, TriangleData Triangle);

void LSvPF();

void PVP();
