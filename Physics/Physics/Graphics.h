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

void InitGL(int argc, char** argv);