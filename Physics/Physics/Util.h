#pragma once

class Vector3 {
public:
	float x;
	float y;
	float z;
};

class Vector2 {
public:
	float x;
	float y;
};

class TriangleData {
public:
	Vector3 firstPoint = { -9999,-9999,0 };
	Vector3 secondPoint = { -9999,-9999,0 };
	Vector3 thirdPoint = { -9999,-9999,0 };
};