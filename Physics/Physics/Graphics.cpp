#include "Graphics.h"

Scene mScene;

Vector2 ScreenSize = {500,500};
Vector2 MousePosition;
TriangleData Triangle;
Vector2 Line;

bool mouseDisable = false; //helps against double click

void CutATriangle(GameObject &triangle, GameObject &line) {

	Vector3 abovePlane[] = { 0,0,0,0 };
	Vector3 belowPlane[] = { 0,0,0,0 };



}

void mouse(int button, int state, int x, int y) { //Click

	if (button == 0) {
		mouseDisable = !mouseDisable; //toggle bool

		if (!mouseDisable) {

			wcout << L"Mouse X:" << MousePosition.x << L" Y:" << MousePosition.y << endl;

			if (Triangle.firstPoint.x == -9999) {
				Triangle.firstPoint.x = MousePosition.x;
				Triangle.firstPoint.y = MousePosition.y;
				wcout << L"Set first point for triangle at: " << Triangle.firstPoint.x << ":" << Triangle.firstPoint.y << endl;
			}
			else if (Triangle.secondPoint.x == -9999) {
				Triangle.secondPoint.x = MousePosition.x;
				Triangle.secondPoint.y = MousePosition.y;
				wcout << L"Set second point for triangle at: " << Triangle.secondPoint.x << ":" << Triangle.secondPoint.y << endl;
			}
			else if (Triangle.thirdPoint.x == -9999) {
				Triangle.thirdPoint.x = MousePosition.x;
				Triangle.thirdPoint.y = MousePosition.y;
				wcout << L"Set third point for triangle at: " << Triangle.thirdPoint.x << ":" << Triangle.thirdPoint.y << endl;
				
				mScene.GameObjects.push_back(new GameObject(Triangle, &mScene.GameObjects));
				wcout << L"Triangle Made" << endl;
			}
		}

	}
	
}

void mouseMovement(int x, int y) {
	float aX = (float(x) - (ScreenSize.x / 2)) / (ScreenSize.x / 2);
	float aY = (float(y) - (ScreenSize.y / 2)) / (ScreenSize.y / 2);
	//wcout << L"Adjusted X:" << aX << L" Y:" << aY << endl;
	MousePosition = { aX, aY };
}

void keyboard(unsigned char key, int, int) {
	

	if (key == 116 || key == 84) { //T Key
		wcout << L"RESET TRIANGLE" << endl;
		Triangle.firstPoint = { -9999, -9999 };
		Triangle.secondPoint = { -9999, -9999 };
		Triangle.thirdPoint = { -9999, -9999 };
		for (size_t i = 0; i < mScene.GameObjects.size(); i++)
		{
			if (mScene.GameObjects.at(i)->type == GameObject::TRIANGLE)
			{
				mScene.GameObjects.at(i)->~GameObject();
				mScene.GameObjects.erase(mScene.GameObjects.begin() + i);
			}
		}
	}
	else if (key == 108 || key == 76) { //L Key
		wcout << L"RESET LINE" << endl;
		Line.x = -9999;
		Line.y = -9999;
	}

}

void keyboardSpecial(int key, int, int) {

}

void Update() {
	
}

void Render() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	for (size_t i = 0; i < mScene.GameObjects.size(); i++) //Render Objects
	{
		mScene.GameObjects.at(i)->Render();
	}

	glutSwapBuffers();
}

void InitGL(int argc, char **argv)
{
	Console_OutputLog(L"OpenGL Service Setting Up...", LOGINFO);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(ScreenSize.x, ScreenSize.y);

	glutCreateWindow("Viewport");

	if (glewInit() != GLEW_OK) {
		Console_OutputLog(L"Glew INIT FAILED! The program cannot recover from this error", LOGFATAL);
		system("pause");
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glClearColor(1.0, 0.0, 0.0, 1.0);

	//Start

	Console_OutputLog(L"OpenGL Service Starting...", LOGINFO);

	glutDisplayFunc(Render);

	glutIdleFunc(Update);

	 // handlers for keyboard input
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);

	// mouse event handlers
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMovement);

	glutMainLoop();

}

GameObject::GameObject(Vector2 positions)
{
	this->type = GameObject::LINE;
}

GameObject::GameObject(TriangleData positions, vector<GameObject*>* sceneList)
{
	this->type = GameObject::TRIANGLE;
	this->triangleData = positions;
	this->vertices[0] = { this->triangleData.firstPoint.x, this->triangleData.firstPoint.y, 0,};
	this->vertices[1] = { this->triangleData.secondPoint.x, this->triangleData.secondPoint.y, 0, };
	this->vertices[2] = { this->triangleData.thirdPoint.x, this->triangleData.thirdPoint.y, 0, };

	this->program = ShaderLoader::CreateProgram("Resources/triangle.vs", "Resources/triangle.fs");

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_STATIC_DRAW);

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//push this gameobject to a scene

	sceneList->push_back(this);

}

GameObject::~GameObject()
{
}

void GameObject::Render()
{
	glClearColor(1.0, 1.0, 0.0, 1.0);

	glUseProgram(this->program);
	
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}


