#pragma once
#include <glew.h>
#include <freeglut.h>
#include <vector>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <ft2build.h>
#include <limits>

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
		CAPSULE,
		POINT
	};
	
	GameObject(LineData positions, float lineWidth); //line
	GameObject(TriangleData positions); //triangle
	GameObject(PointData _point); //triangle
	GameObject(CircleData inCircle1, CircleData inCircle2); //capsule
	~GameObject();
	objectType type;
	
	void Render();

	LineData getLineData();
	TriangleData getTriangleData();
	LineData lineData;
	TriangleData triangleData;
	CapsuleData capsuleData;
	PointData pointData;

	bool killMe = false;
	float lineWidth = 1.0f;

private:

	
	Vector3 color = {0,0,0};

};

class Scene {
public:
	enum scenes {
		TRIANGLE,
		CAPSULE,
		PIT,
		PITB
	};
	vector<GameObject*> GameObjects;
	scenes currentScene = TRIANGLE;
	bool drawingTriangle = true;

};

void CutATriangle(GameObject* triangle, GameObject* line);

void mouse(int button, int state, int x, int y);

void InitGL(int argc, char** argv, Scene::scenes currentScene);
