#pragma once
#include <glew.h>
#include <freeglut.h>
#include <vector>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <ft2build.h>

#include "ConsoleController.h"
#include "ShaderLoader.h"
#include "Physics.h"
#include "Util.h"

using namespace std;

class GameObject {
public:
	enum objectType {
		UNDEFINIED,
		TRIANGLE,
		LINE
	};
	GameObject(LineData positions, vector<GameObject*>* sceneList); //line
	GameObject(TriangleData positions, vector<GameObject*>* sceneList); //triangle
	~GameObject();
	objectType type;
	
	void Render();

	LineData getLineData();
	TriangleData getTriangleData();

private:

	LineData lineData;
	TriangleData triangleData;
	Vector3 color = {0,0,0};

};

class Scene {
public:
	vector<GameObject*> GameObjects;
	bool drawingTriangle = true;

};

void InitGL(int argc, char** argv);