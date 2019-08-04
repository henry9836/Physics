#pragma once
#include <glew.h>
#include <freeglut.h>
#include <vector>

#include "ConsoleController.h"

using namespace std;

class GameObject {
public:
	enum objectType {
		UNDEFINIED,
		TRIANGLE,
		LINE
	};
	GameObject(objectType type);
	~GameObject();
};

class Scene {
public:
	vector<GameObject*> GameObjects;
	bool drawingTriangle = true;
	
};

void InitGL(int argc, char** argv);