#pragma once

struct Vector3 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

struct Vector2 {
	float x = 0.0f;
	float y = 0.0f;
};

struct TriangleData {
	Vector3 firstPoint =  { -9999, -9999, 0 };
	Vector3 secondPoint = { -9999, -9999, 0 };
	Vector3 thirdPoint =  { -9999, -9999, 0 };
};

struct LineData {
	Vector3 firstPoint =  { -9999, -9999, 0 };
	Vector3 secondPoint = { -9999, -9999, 0 };
};
