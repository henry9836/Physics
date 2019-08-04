#pragma once

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Vector2 {
	float x;
	float y;
};

struct TriangleData {
	Vector3 firstPoint = { -9999,-9999,0 };
	Vector3 secondPoint = { -9999,-9999,0 };
	Vector3 thirdPoint = { -9999,-9999,0 };
};