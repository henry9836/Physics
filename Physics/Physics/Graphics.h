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
	GameObject(TriangleData positions, vector<GameObject*>* sceneList); //triangle
	~GameObject();
	objectType type;
	
	void Render();

private:

	TriangleData triangleData;
	GLuint program = NULL;
	GLuint texture = NULL;
	GLuint VAO = NULL;
	GLuint VBO = NULL;
	GLuint EBO = NULL;
	Vector3 vertices[24] = { 0.0f,0.0f,0.0f, 1.0f,0.0f,0.0f,  0.0f, 0.0f,
							 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f,  0.0f, 1.0f,
							 0.0f,0.0f,0.0f, 0.0f,0.0f,1.0f,  1.0f, 1.0f, };
	GLuint indices[6] = {0,1,2,
						 0,2,3};

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