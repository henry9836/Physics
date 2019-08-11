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
#include "Lagrange.h"

using namespace std;

class GameObject {
public:
	enum objectType {
		UNDEFINIED,
		TRIANGLE,
		LINE,
		CAPSULE
	};
	
	GameObject(LineData positions); //line
	GameObject(TriangleData positions); //triangle
	GameObject(CircleData inCircle1, CircleData inCircle2); //capsule
	~GameObject();
	objectType type;
	
	void Render();

	LineData getLineData();
	TriangleData getTriangleData();
	LineData lineData;
	TriangleData triangleData;
	CapsuleData capsuleData;
	bool killMe = false;

private:

	
	Vector3 color = {0,0,0};

};

class Scene {
public:
	enum scenes {
		TRIANGLE,
		CAPSULE
	};
	vector<GameObject*> GameObjects;
	scenes currentScene = TRIANGLE;
	bool drawingTriangle = true;

};

void CutATriangle(GameObject* triangle, GameObject* line);

void mouse(int button, int state, int x, int y);

void InitGL(int argc, char** argv, Scene::scenes currentScene);
