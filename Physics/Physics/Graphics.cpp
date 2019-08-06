#include "Graphics.h"

Scene mScene;

IntVector2 ScreenSize = {500,500};
Vector2 MousePosition;
TriangleData Triangle;
LineData Line;

bool mouseDisable = false; //helps against double click

void CutATriangle(GameObject* triangle, GameObject* line) {

	Console_OutputLog(L"Attempting To Slice Triangle", LOGINFO);

	triangle->killMe = true;

	vector<Vector3> Below;
	vector<Vector3> Above;
	vector<Vector2> splitPositions;

	//split off easy triangle

	//assign first vert

	Above.push_back(triangle->getTriangleData().firstPoint);

	//find a intersect points
	
	Vector3 d = ((line->lineData.firstPoint) - (line->lineData.secondPoint)); //d is distance

	Vector3 p1 = (triangle->triangleData.firstPoint - triangle->triangleData.secondPoint); //get a point on the first line
	float i1 = (CrossProduct((line->lineData.firstPoint - triangle->triangleData.firstPoint),d) / CrossProduct(d, p1)).z; //get distance from p1 to intersect

	Vector3 p2 = (triangle->triangleData.secondPoint - triangle->triangleData.thirdPoint); //get a point on the first line
	float i2 = (CrossProduct((line->lineData.firstPoint - triangle->triangleData.secondPoint), d) / CrossProduct(d, p2)).z; //get distance from p2 to intersect

	Vector3 p3 = (triangle->triangleData.thirdPoint - triangle->triangleData.firstPoint); //get a point on the first line
	float i3 = (CrossProduct((line->lineData.firstPoint - triangle->triangleData.thirdPoint), d) / CrossProduct(d, p3)).z; //get distance from p3 to intersect

	Vector3 collisionPoint1;
	Vector3 collisionPoint2;
	Vector3 collisionPoint3;

	if (i1 <= 1.0f && i1 >= 0.0f)  {
		collisionPoint1 = (triangle->triangleData.firstPoint - (p1 * i1));
	}
	if (i2 <= 1.0f && i2 >= 0.0f) {
		collisionPoint2 = (triangle->triangleData.secondPoint - (p2 * i2));
	}
	if (i3 <= 1.0f && i3 >= 0.0f) {
		collisionPoint3 = (triangle->triangleData.thirdPoint - (p3 * i3));
	}

	

	//create three triangles

	bool cutSucc = false;

	TriangleData t1;
	TriangleData t2;
	TriangleData t3;

	if (collisionPoint1 != Vector3{0,0,0} && collisionPoint2 != Vector3{ 0,0,0 }) {

		t1.firstPoint = triangle->triangleData.firstPoint;
		t1.secondPoint = collisionPoint1;
		t1.thirdPoint = triangle->triangleData.thirdPoint;

		t2.firstPoint = triangle->triangleData.secondPoint;
		t2.secondPoint = collisionPoint1;
		t2.thirdPoint = collisionPoint2;

		t3.firstPoint = triangle->triangleData.thirdPoint;
		t3.secondPoint = collisionPoint1;
		t3.thirdPoint = collisionPoint2;

		cutSucc = true;
	}

	if (collisionPoint1 != Vector3{ 0,0,0 } && collisionPoint3 != Vector3{ 0,0,0 }) {

		t1.firstPoint = triangle->triangleData.firstPoint;
		t1.secondPoint = collisionPoint1;
		t1.thirdPoint = collisionPoint3;

		t2.firstPoint = collisionPoint1;
		t2.secondPoint = triangle->triangleData.secondPoint;
		t2.thirdPoint = collisionPoint3;

		t3.firstPoint = collisionPoint3;
		t3.secondPoint = triangle->triangleData.secondPoint;
		t3.thirdPoint = triangle->triangleData.thirdPoint;

		cutSucc = true;
	}

	if (collisionPoint2 != Vector3{ 0,0,0 } && collisionPoint3 != Vector3{ 0,0,0 }) {

		t1.firstPoint = triangle->triangleData.firstPoint;
		t1.secondPoint = triangle->triangleData.secondPoint;
		t1.thirdPoint = collisionPoint2;

		t2.firstPoint = triangle->triangleData.firstPoint;
		t2.secondPoint = collisionPoint2;
		t2.thirdPoint = collisionPoint3;

		t3.firstPoint = collisionPoint3;
		t3.secondPoint = collisionPoint2;
		t3.thirdPoint = triangle->triangleData.thirdPoint;

		cutSucc = true;
	}
	

	if (cutSucc) {
		//Clean GameObjects
		Console_OutputLog(L"Cleaning Scene", LOGINFO);
		Line.firstPoint.x = -9999;
		Line.secondPoint.x = -9999;
		for (size_t i = 0; i < mScene.GameObjects.size(); i++)
		{
			if (mScene.GameObjects.at(i)->killMe) {
				Console_OutputLog(L"Removing Tagged GameObject", LOGINFO);
				mScene.GameObjects.at(i)->~GameObject();
				mScene.GameObjects.erase(mScene.GameObjects.begin() + i);
				i--;
			}
			
		}
		for (size_t i = 0; i < mScene.GameObjects.size(); i++)
		{
			if (mScene.GameObjects.at(i)->type == GameObject::LINE)
			{
				Console_OutputLog(L"Removing Line", LOGINFO);
				mScene.GameObjects.at(i)->~GameObject();
				mScene.GameObjects.erase(mScene.GameObjects.begin() + i);
				i--;
			}
		}
		
		mScene.GameObjects.push_back(new GameObject(t1));
		mScene.GameObjects.push_back(new GameObject(t2));
		mScene.GameObjects.push_back(new GameObject(t3));
		Console_OutputLog(L"Sliced Triangle", LOGINFO);
	}

	else {
		Console_OutputLog(L"Could not find a collison to cut triangle", LOGWARN);
	}

	

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

				mScene.GameObjects.push_back(new GameObject(Triangle));
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

				mScene.GameObjects.push_back(new GameObject(Line));

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
		Console_OutputLog(L"Reset Triangles", LOGINFO);
		Triangle.firstPoint = { -9999, -9999,0 };
		Triangle.secondPoint = { -9999, -9999,0 };
		Triangle.thirdPoint = { -9999, -9999,0 };
		for (size_t i = 0; i < mScene.GameObjects.size(); i++)
		{
			if (mScene.GameObjects.at(i)->type == GameObject::TRIANGLE)
			{
				mScene.GameObjects.at(i)->~GameObject();
				mScene.GameObjects.erase(mScene.GameObjects.begin() + i);
				i--;
			}
		}
	}
	else if (key == 108 || key == 76) { //L Key
		Console_OutputLog(L"Reset Line", LOGINFO);
		Line.firstPoint.x = -9999;
		Line.secondPoint.x = -9999;
		for (size_t i = 0; i < mScene.GameObjects.size(); i++)
		{
			if (mScene.GameObjects.at(i)->type == GameObject::LINE)
			{
				mScene.GameObjects.at(i)->~GameObject();
				mScene.GameObjects.erase(mScene.GameObjects.begin() + i);
				i--;
			}
		}
	}
	else if (key == 13 || key == 32) { // Return/Space Key
		wcout << L"Cut!" << endl;
		GameObject* tmpTriangle = NULL;
		GameObject* tmpLine = NULL;
		for (size_t i = 0; i < mScene.GameObjects.size(); i++)
		{
			if (mScene.GameObjects.at(i)->type == GameObject::TRIANGLE) {
				tmpTriangle = mScene.GameObjects.at(i);
			}
			if (mScene.GameObjects.at(i)->type == GameObject::LINE) {
				tmpLine = mScene.GameObjects.at(i);
			}
		}
		if (tmpTriangle != NULL && tmpLine != NULL) {
			CutATriangle(tmpTriangle, tmpLine);
			tmpTriangle = NULL;
			delete tmpLine;
		}
		else {
			Console_OutputLog(L"Could not find any valid triangles or lines to use", LOGWARN);
		}
		
	}
	else if (key == 27 || key == 81 || key == 113) {
		Console_OutputLog(L"Exitting OpenGL...", LOGINFO);
		glutLeaveMainLoop();
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

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

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

GameObject::GameObject(LineData positions)
{
	this->type = GameObject::LINE;
	this->lineData = positions;

	this->color = Vector3{ (float)(rand() % 255) / 255  , (float)(rand() % 255) / 255, (float)(rand() % 255) / 255 };
}

GameObject::GameObject(TriangleData positions)
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


