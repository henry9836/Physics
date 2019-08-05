#include "Graphics.h"

Scene mScene;

Vector2 ScreenSize = {500,500};
Vector2 MousePosition;
TriangleData Triangle;
LineData Line;

bool mouseDisable = false; //helps against double click

void CutATriangle(GameObject* triangle, GameObject* line) {

	vector<Vector3> Below;
	vector<Vector3> Above;
	vector<Vector2> splitPositions;

	//split off easy triangle

	//assign first vert

	Above.push_back(triangle->getTriangleData().firstPoint);

	//find a intersect point
	
	LinevPlane();


	//create two more triangles
	

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
			else if (Line.firstPoint.x == -9999) {
				Line.firstPoint.x = MousePosition.x;
				Line.firstPoint.y = MousePosition.y;
				wcout << L"Set first point for line at: " << Line.firstPoint.x << ":" << Line.firstPoint.y << endl;
			}
			else if (Line.secondPoint.x == -9999) {
				Line.secondPoint.x = MousePosition.x;
				Line.secondPoint.y = MousePosition.y;
				wcout << L"Set second point for line at: " << Line.secondPoint.x << ":" << Line.secondPoint.y << endl;

				mScene.GameObjects.push_back(new GameObject(Line, &mScene.GameObjects));

				wcout << L"Line Made" << endl;
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
		Line.firstPoint.x = -9999;
		Line.secondPoint.x = -9999;
		for (size_t i = 0; i < mScene.GameObjects.size(); i++)
		{
			if (mScene.GameObjects.at(i)->type == GameObject::LINE)
			{
				mScene.GameObjects.at(i)->~GameObject();
				mScene.GameObjects.erase(mScene.GameObjects.begin() + i);
			}
		}
	}
	else if (key == 13 || key == 32) { // Return/Space Key
		wcout << L"Cut!" << endl;
		CutATriangle(&Triangle, &Line);
	}

}

void keyboardSpecial(int key, int, int) {

}


void Render() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	for (size_t i = 0; i < mScene.GameObjects.size(); i++) //Render Objects
	{
		mScene.GameObjects.at(i)->Render();
	}

	glutSwapBuffers();
}

void Update() {
	Render();
}

void InitGL(int argc, char **argv)
{
	srand(static_cast <unsigned> (time(0)));
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

GameObject::GameObject(LineData positions, vector<GameObject*>* sceneList)
{
	this->type = GameObject::LINE;
	this->lineData = positions;

	this->color = Vector3{ (float)(rand() % 255) / 255  , (float)(rand() % 255) / 255, (float)(rand() % 255) / 255 };
}

GameObject::GameObject(TriangleData positions, vector<GameObject*>* sceneList)
{
	this->type = GameObject::TRIANGLE;
	this->triangleData = positions;
	
	this->color = Vector3{ (float)(rand() % 255) / 255  , (float)(rand() % 255) / 255, (float)(rand() % 255) / 255 };


	//push this gameobject to a scene

	//sceneList->push_back(this);

}

GameObject::~GameObject()
{
}

void GameObject::Render()
{

	if (this->type == GameObject::TRIANGLE) {

		glBegin(GL_TRIANGLES);

		glColor3f(this->color.x, this->color.y, this->color.z);

		glVertex3f(this->triangleData.firstPoint.x, -this->triangleData.firstPoint.y, 0);
		glVertex3f(this->triangleData.secondPoint.x, -this->triangleData.secondPoint.y, 0);
		glVertex3f(this->triangleData.thirdPoint.x, -this->triangleData.thirdPoint.y, 0);

		glEnd();
	}
	else if (this->type == GameObject::LINE) {
		glBegin(GL_LINES);

		glColor3f(this->color.x, this->color.y, this->color.z);

		glVertex3f(this->lineData.firstPoint.x, -this->lineData.firstPoint.y, 0);
		glVertex3f(this->lineData.secondPoint.x, -this->lineData.secondPoint.y, 0);

		glEnd();
	}
}

LineData GameObject::getLineData()
{
	return this->lineData;
}

TriangleData GameObject::getTriangleData()
{
	return this->triangleData;
}


