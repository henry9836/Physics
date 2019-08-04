#pragma once
#include <glew.h>
#include <freeglut.h>
#include <vector>

#include "ConsoleController.h"

using namespace std;


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
	Vector2 firstPoint = {-9999,-9999};
	Vector2 secondPoint = { -9999,-9999 };
	Vector2 thirdPoint = { -9999,-9999 };
};

class GameObject {
public:
	enum objectType {
		UNDEFINIED,
		TRIANGLE,
		LINE
	};
	GameObject(Vector2 positions); //line
	GameObject(TriangleData positions); //triangle
	~GameObject();

	TriangleData triangleData;
	objectType type;
	void Render();
};

class Scene {
public:
	vector<GameObject*> GameObjects;
	bool drawingTriangle = true;
	
};

class Util {
public:
	vector<int> ScreenSize = { 500,500 };
	vector<float> MousePosition = { 0.0,0.0 };
};



void InitGL(int argc, char** argv);