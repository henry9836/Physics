#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include "Graphics.h"
#include "Util.h"

using namespace std;

float dotproduct(Vector3 VECA, Vector3 VECB);

vector<float> mutiplay(float times, vector<float> OG);

Vector3 vsubtract(Vector3 first, Vector3 second);

void TrianglePlaneFunction(Vector3 plane, Vector3 planeNormal, TriangleData Triangle);

float LinevPlane(Vector3 planePosition, Vector3 planeNormal, LineData linePositions);

void PlanevPoint(Vector3 planePosition, Vector3 planeNormal, Vector3 pointPosition);

Vector3 findPerpendicular(Vector3 pointA, Vector3 pointB);

void javelin();

bool PointInTriangle(glm::vec2 pt, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3);

bool PointInTriangleBarycentric(glm::vec2 pt, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3);
