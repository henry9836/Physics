#include "Graphics.h"

Scene mScene;

IntVector2 ScreenSize = {500,500};
Vector2 MousePosition;
TriangleData Triangle;
LineData Line;
PointData point;
CircleData FirstCircle;
CircleData SecondCircle;
CircleData ThirdCircle;
CircleData FourthCircle;
FivePointShape fivePointShapeOne;
FivePointShape fivePointShapeTwo;

bool mouseDisable = false; //helps against double click

void ResetObjects() {
	FirstCircle.centerPoint.x = -9999;
	SecondCircle.centerPoint.x = -9999;
	ThirdCircle.centerPoint.x = -9999;
	FourthCircle.centerPoint.x = -9999;
	FirstCircle.radius = -9999;
	SecondCircle.radius = -9999;
	ThirdCircle.radius = -9999;
	FourthCircle.radius = -9999;
	Triangle.firstPoint.x = -9999;
	Triangle.thirdPoint.x = -9999;
	Triangle.secondPoint.x = -9999;
	point.data.x = -9999;
	fivePointShapeOne.firstPoint.x = -9999;
	fivePointShapeOne.secondPoint.x = -9999;
	fivePointShapeOne.thirdPoint.x = -9999;
	fivePointShapeOne.fourthPoint.x = -9999;
	fivePointShapeOne.fifthPoint.x = -9999;
	fivePointShapeTwo.firstPoint.x = -9999;
	fivePointShapeTwo.secondPoint.x = -9999;
	fivePointShapeTwo.thirdPoint.x = -9999;
	fivePointShapeTwo.fourthPoint.x = -9999;
	fivePointShapeTwo.fifthPoint.x = -9999;
}

void drawLineCapsuleDistance(CapsuleData capsule1, CapsuleData capsule2) {
	float shortestDistance = 999999;

	vector<CircleData> circles;
	LineData collisonLine;

	circles.push_back(capsule1.circle1);
	circles.push_back(capsule1.circle2);
	circles.push_back(capsule2.circle1);
	circles.push_back(capsule2.circle2);


	//Invert ys
	for (size_t i = 0; i < circles.size(); i++)
	{
		circles[i].centerPoint.y *= -1;
	}

	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			float distance = (sqrt(pow((circles[i].centerPoint.x - circles[j + 2].centerPoint.x), 2) + pow((circles[i].centerPoint.y - circles[j + 2].centerPoint.y), 2)));

			if (distance < shortestDistance) {
				shortestDistance = distance;
				collisonLine.firstPoint = circles[i].centerPoint;
				collisonLine.secondPoint = circles[j + 2].centerPoint;
				Console_OutputLog(L"Distance Updated", LOGINFO);
			}
		}
	}

	if (capsule1.circle1.radius + capsule2.circle1.radius >= shortestDistance)
	{
		std::wcout << "Collision Detected\n";
	}

	Vector3 dir = circles[1].centerPoint - circles[0].centerPoint;

	float magintude = sqrt(pow(dir.x, 2) + pow(dir.y, 2));

	Vector3 a = collisonLine.secondPoint - circles[0].centerPoint;
	Vector3 b = ((circles[1].centerPoint - circles[0].centerPoint) / magintude);

	float t = sqrt((a.x * b.x) + (a.y * b.y));

	if (t <= 0) {
		t = 0;
	}
	else if (t > magintude)
	{
		t = magintude;
	}

	collisonLine.firstPoint = (collisonLine.secondPoint);
	collisonLine.secondPoint = (circles[0].centerPoint + (b * t));

	mScene.GameObjects.push_back(new GameObject(collisonLine, 3.0f));

}

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

float circleSectionBuilder(CircleData* inCircle) {

	float xDiff = (inCircle->centerPoint.x - MousePosition.x);
	float yDiff = (inCircle->centerPoint.y - MousePosition.y);

	if (xDiff < 0) {
		xDiff *= -1;
	}
	if (yDiff < 0) {
		yDiff *= -1;
	}

	float result = sqrt(pow(xDiff, 2) + pow(yDiff, 2));
	wcout << "RADIUS: " << result << endl;
	return result;
}

void mouse(int button, int state, int x, int y) { //Click

	if (button == 0) {
		mouseDisable = !mouseDisable; //toggle bool

		if (!mouseDisable) {

			wcout << L"Mouse X:" << MousePosition.x << L" Y:" << MousePosition.y << endl;
			if (mScene.currentScene == Scene::TRIANGLE) {
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

					mScene.GameObjects.push_back(new GameObject(Line, 1.0f));

					wcout << L"Line Made" << endl;
				}
			}
			else if (mScene.currentScene == Scene::CAPSULE) {
				
				MousePosition.y = -MousePosition.y;

				if (FirstCircle.centerPoint.x == -9999) {
					FirstCircle.centerPoint.x = MousePosition.x;
					FirstCircle.centerPoint.y = MousePosition.y;
				}
				else if (FirstCircle.radius < 0.0f) {
					FirstCircle.radius = circleSectionBuilder(&FirstCircle);
				}
				else if (SecondCircle.centerPoint.x == -9999) {
					SecondCircle.centerPoint.x = MousePosition.x;
					SecondCircle.centerPoint.y = MousePosition.y;
					SecondCircle.radius = FirstCircle.radius;
					mScene.GameObjects.push_back(new GameObject(FirstCircle, SecondCircle));
				}
				else if (ThirdCircle.centerPoint.x == -9999) {
					ThirdCircle.centerPoint.x = MousePosition.x;
					ThirdCircle.centerPoint.y = MousePosition.y;
				}
				else if (ThirdCircle.radius < 0.0f) {
					ThirdCircle.radius = circleSectionBuilder(&ThirdCircle);
				}
				else if (FourthCircle.centerPoint.x == -9999) {
					FourthCircle.centerPoint.x = MousePosition.x;
					FourthCircle.centerPoint.y = MousePosition.y;
					FourthCircle.radius = ThirdCircle.radius;
					mScene.GameObjects.push_back(new GameObject(ThirdCircle, FourthCircle));
				}
			}
			else if (mScene.currentScene == Scene::PIT || mScene.currentScene == Scene::PITB) {
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
				else if (point.data.x == -9999) {

					point.data.x = MousePosition.x;
					point.data.y = MousePosition.y;
					point.data.z = -0.5f;

					wcout << L"Set point at: " << point.data.x << ":" << point.data.y << endl;

					mScene.GameObjects.push_back(new GameObject(point));
					wcout << L"Point Made" << endl;

					if (mScene.currentScene == Scene::PIT) {
						if (PointInTriangle(glm::vec2(point.data.x, point.data.y), glm::vec2(Triangle.firstPoint.x, Triangle.firstPoint.y), glm::vec2(Triangle.secondPoint.x, Triangle.secondPoint.y), glm::vec2(Triangle.thirdPoint.x, Triangle.thirdPoint.y))) {
							Console_OutputLog(L"POINT IS INSIDE TRIANGLE", LOGINFO);
							mScene.GameObjects.push_back(new GameObject(GameObject::LETTERI, glm::vec3(0.7f, -0.9f, -0.9f)));
						}
						else {
							Console_OutputLog(L"POINT IS NOT INSIDE TRIANGLE", LOGINFO);
							mScene.GameObjects.push_back(new GameObject(GameObject::LETTERO, glm::vec3(0.7f, -0.9f, -0.9f)));
						}
					}
					else {
						if (PointInTriangleBarycentric(glm::vec2(point.data.x, point.data.y), glm::vec2(Triangle.firstPoint.x, Triangle.firstPoint.y), glm::vec2(Triangle.secondPoint.x, Triangle.secondPoint.y), glm::vec2(Triangle.thirdPoint.x, Triangle.thirdPoint.y))) {
							Console_OutputLog(L"POINT IS INSIDE TRIANGLE B", LOGINFO);
							mScene.GameObjects.push_back(new GameObject(GameObject::LETTERI, glm::vec3(0.7f, -0.9f, -0.9f)));
						}
						else {
							Console_OutputLog(L"POINT IS NOT INSIDE TRIANGLE B", LOGINFO);
							mScene.GameObjects.push_back(new GameObject(GameObject::LETTERO, glm::vec3(0.7f, -0.9f, -0.9f)));
						}
					}
				}


			}
			else if (mScene.currentScene == Scene::SAT){
				MousePosition.y = -MousePosition.y;
				if (fivePointShapeOne.firstPoint.x == -9999) {
					fivePointShapeOne.firstPoint.x = MousePosition.x;
					fivePointShapeOne.firstPoint.y = MousePosition.y;
					wcout << L"Set point for shape at: " << fivePointShapeOne.firstPoint.x << ":" << fivePointShapeOne.firstPoint.y << endl;
				}
				else if (fivePointShapeOne.secondPoint.x == -9999) {
					fivePointShapeOne.secondPoint.x = MousePosition.x;
					fivePointShapeOne.secondPoint.y = MousePosition.y;
					wcout << L"Set point for shape at: " << fivePointShapeOne.secondPoint.x << ":" << fivePointShapeOne.secondPoint.y << endl;
				}
				else if (fivePointShapeOne.thirdPoint.x == -9999) {
					fivePointShapeOne.thirdPoint.x = MousePosition.x;
					fivePointShapeOne.thirdPoint.y = MousePosition.y;
					wcout << L"Set point for shape at: " << fivePointShapeOne.thirdPoint.x << ":" << fivePointShapeOne.thirdPoint.y << endl;
				}
				else if (fivePointShapeOne.fourthPoint.x == -9999) {
					fivePointShapeOne.fourthPoint.x = MousePosition.x;
					fivePointShapeOne.fourthPoint.y = MousePosition.y;
					wcout << L"Set point for shape at: " << fivePointShapeOne.fourthPoint.x << ":" << fivePointShapeOne.fourthPoint.y << endl;
				}
				else if (fivePointShapeOne.fifthPoint.x == -9999) {
					fivePointShapeOne.fifthPoint.x = MousePosition.x;
					fivePointShapeOne.fifthPoint.y = MousePosition.y;
					wcout << L"Set point for shape at: " << fivePointShapeOne.fifthPoint.x << ":" << fivePointShapeOne.fifthPoint.y << endl;
					mScene.GameObjects.push_back(new GameObject(fivePointShapeOne));
				}
				else if (fivePointShapeTwo.firstPoint.x == -9999) {
					fivePointShapeTwo.firstPoint.x = MousePosition.x;
					fivePointShapeTwo.firstPoint.y = MousePosition.y;
					wcout << L"Set point for shape at: " << fivePointShapeTwo.firstPoint.x << ":" << fivePointShapeTwo.firstPoint.y << endl;
				}
				else if (fivePointShapeTwo.secondPoint.x == -9999) {
					fivePointShapeTwo.secondPoint.x = MousePosition.x;
					fivePointShapeTwo.secondPoint.y = MousePosition.y;
					wcout << L"Set point for shape at: " << fivePointShapeTwo.secondPoint.x << ":" << fivePointShapeTwo.secondPoint.y << endl;
				}
				else if (fivePointShapeTwo.thirdPoint.x == -9999) {
					fivePointShapeTwo.thirdPoint.x = MousePosition.x;
					fivePointShapeTwo.thirdPoint.y = MousePosition.y;
					wcout << L"Set point for shape at: " << fivePointShapeTwo.thirdPoint.x << ":" << fivePointShapeTwo.thirdPoint.y << endl;
				}
				else if (fivePointShapeTwo.fourthPoint.x == -9999) {
					fivePointShapeTwo.fourthPoint.x = MousePosition.x;
					fivePointShapeTwo.fourthPoint.y = MousePosition.y;
					wcout << L"Set point for shape at: " << fivePointShapeTwo.fourthPoint.x << ":" << fivePointShapeTwo.fourthPoint.y << endl;
				}
				else if (fivePointShapeTwo.fifthPoint.x == -9999) {
					fivePointShapeTwo.fifthPoint.x = MousePosition.x;
					fivePointShapeTwo.fifthPoint.y = MousePosition.y;
					wcout << L"Set point for shape at: " << fivePointShapeTwo.fifthPoint.x << ":" << fivePointShapeTwo.fifthPoint.y << endl;
					mScene.GameObjects.push_back(new GameObject(fivePointShapeTwo));
				}
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
	
	if (mScene.currentScene == Scene::TRIANGLE) {
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
	}
	else if (mScene.currentScene == Scene::CAPSULE) {
		if (key == 27 || key == 114 || key == 82) { //esc/r to reset
			for (size_t i = 0; i < mScene.GameObjects.size(); i++)
			{
				mScene.GameObjects.at(i)->~GameObject();
				mScene.GameObjects.erase(mScene.GameObjects.begin() + i);
				i--;
			}
			ResetObjects();
		}
		else if (key == 13 || key == 32) {
			CapsuleData tmp1, tmp2;

			bool gotCaps = false;

			for (size_t i = 0; i < mScene.GameObjects.size(); i++)
			{
				if (mScene.GameObjects[i]->type == GameObject::CAPSULE) {
					if (tmp1.circle1.centerPoint.x == -9999) {
						tmp1 = mScene.GameObjects[i]->capsuleData;
					}
					else {
						tmp2 = mScene.GameObjects[i]->capsuleData;
						gotCaps = true;
					}
				}
			}

			if (gotCaps) {
				drawLineCapsuleDistance(tmp1, tmp2);
			}
		}
		//wcout << key << endl;
	}
	else if (mScene.currentScene == Scene::PIT || mScene.currentScene == Scene::PITB || mScene.currentScene == Scene::SAT) {
		if (key == 114 || key == 82) { //r to reset
			for (size_t i = 0; i < mScene.GameObjects.size(); i++)
			{
				mScene.GameObjects.at(i)->~GameObject();
				mScene.GameObjects.erase(mScene.GameObjects.begin() + i);
				i--;
			}
			ResetObjects();
		}
	}
	if (key == 27) { //esc
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

void InitGL(int argc, char** argv, Scene::scenes currentScene)
{

	//Init/Reset Values

	mScene.currentScene = currentScene;

	for (size_t i = 0; i < mScene.GameObjects.size(); i++)
	{

		mScene.GameObjects.at(i)->~GameObject();
		mScene.GameObjects.erase(mScene.GameObjects.begin() + i);
		i--;
	}

	ResetObjects();
		
	//Start OpenGL

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

	glClearColor(0.0, 0.0, 0.0, 1.0);

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

GameObject::GameObject(LineData positions, float lineWidth)
{
	this->type = GameObject::LINE;
	this->lineData = positions;
	this->lineWidth = lineWidth;

	this->color = Vector3{ (float)(rand() % 255) / 255  , (float)(rand() % 255) / 255, (float)(rand() % 255) / 255 };
}

GameObject::GameObject(TriangleData positions)
{
	this->type = GameObject::TRIANGLE;
	this->triangleData = positions;
	
	this->color = Vector3{ (float)(rand() % 255) / 255  , (float)(rand() % 255) / 255, (float)(rand() % 255) / 255 };

}

GameObject::GameObject(PointData _point)
{
	this->type = GameObject::POINT;

	this->pointData = _point;

	this->color = Vector3{ (float)(rand() % 255) / 255  , (float)(rand() % 255) / 255, (float)(rand() % 255) / 255 };
}

GameObject::GameObject(CircleData inCircle1, CircleData inCircle2)
{
	this->type = GameObject::CAPSULE;
	
	this->capsuleData.circle1 = inCircle1;
	this->capsuleData.circle2 = inCircle2;

	this->color = Vector3{ (float)(rand() % 255) / 255  , (float)(rand() % 255) / 255, (float)(rand() % 255) / 255 };
}

GameObject::GameObject(objectType letter, glm::vec3 pos)
{
	this->type = letter;
	this->pointData.data.x = pos.x;
	this->pointData.data.y = pos.y;
	this->pointData.data.z = pos.z;
}

GameObject::GameObject(FivePointShape _fiveshapeData)
{
	this->type = GameObject::FIVESHAPE;
	this->fiveshapeData = _fiveshapeData;

	this->color = Vector3{ (float)(rand() % 255) / 255  , (float)(rand() % 255) / 255, (float)(rand() % 255) / 255 };
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

		glLineWidth(this->lineWidth);
		glColor3f(this->color.x, this->color.y, this->color.z);

		glVertex3f(this->lineData.firstPoint.x, -this->lineData.firstPoint.y, 0);
		glVertex3f(this->lineData.secondPoint.x, -this->lineData.secondPoint.y, 0);

		glEnd();
	}
	else if (this->type == GameObject::CAPSULE) {
		

		//Draw Circles

		glBegin(GL_TRIANGLE_FAN);

		glColor3f(this->color.x, this->color.y, this->color.z);

		glVertex3f(this->capsuleData.circle1.centerPoint.x, this->capsuleData.circle1.centerPoint.y, 0.0f);

		for (int i = 0; i < 365; ++i) {
			float angle = i * 3.1415926535897932384626433832795f / 180.0f;
			glVertex3f((this->capsuleData.circle1.centerPoint.x + std::cos(angle) * this->capsuleData.circle1.radius), (this->capsuleData.circle1.centerPoint.y + std::sin(angle) * this->capsuleData.circle1.radius), 0);
		}

		glEnd();



		glBegin(GL_TRIANGLE_FAN);

		glColor3f(this->color.x, this->color.y, this->color.z);

		glVertex3f(this->capsuleData.circle2.centerPoint.x, this->capsuleData.circle2.centerPoint.y, 0.0f);

		for (int i = 0; i < 365; ++i) {
			float angle = i * 3.1415926535897932384626433832795f / 180.0f;
			glVertex3f((this->capsuleData.circle2.centerPoint.x + std::cos(angle) * this->capsuleData.circle2.radius), (this->capsuleData.circle2.centerPoint.y + std::sin(angle) * this->capsuleData.circle2.radius), 0);
		}

		glEnd();


		//Draw Box

		glBegin(GL_TRIANGLES);

		glColor3f(this->color.x, this->color.y, this->color.z);

		Vector3 Perpendicular = findPerpendicular(this->capsuleData.circle1.centerPoint, this->capsuleData.circle2.centerPoint);

		//topleft
		glVertex3f(this->capsuleData.circle1.centerPoint.x + Perpendicular.x * this->capsuleData.circle1.radius, this->capsuleData.circle1.centerPoint.y + Perpendicular.y * this->capsuleData.circle1.radius, 0.0f);
		//topright
		glVertex3f(this->capsuleData.circle2.centerPoint.x - Perpendicular.x * this->capsuleData.circle2.radius, this->capsuleData.circle2.centerPoint.y - Perpendicular.y * this->capsuleData.circle2.radius, 0.0f);
		//bottomleft
		glVertex3f(this->capsuleData.circle1.centerPoint.x - Perpendicular.x * this->capsuleData.circle1.radius, this->capsuleData.circle1.centerPoint.y - Perpendicular.y * this->capsuleData.circle1.radius, 0.0f);
		//topright
		glVertex3f(this->capsuleData.circle2.centerPoint.x - Perpendicular.x * this->capsuleData.circle2.radius, this->capsuleData.circle2.centerPoint.y - Perpendicular.y * this->capsuleData.circle2.radius, 0.0f);
		//bottomright
		glVertex3f(this->capsuleData.circle2.centerPoint.x + Perpendicular.x * this->capsuleData.circle2.radius, this->capsuleData.circle2.centerPoint.y + Perpendicular.y * this->capsuleData.circle2.radius, 0.0f);
		//bottomleft?
		glVertex3f(this->capsuleData.circle1.centerPoint.x + Perpendicular.x * this->capsuleData.circle1.radius, this->capsuleData.circle1.centerPoint.y + Perpendicular.y * this->capsuleData.circle1.radius, 0.0f);

		glEnd();
	}
	else if (this->type == GameObject::POINT) {
		glPointSize(10.0f);
		glBegin(GL_POINTS);
		
		glColor3f(this->color.x, this->color.y, this->color.z);
		
		glVertex3f(point.data.x, -point.data.y, point.data.z);

		glEnd();
	}
	else if (this->type == GameObject::LETTERI) {
		glm::vec3 orgin = glm::vec3(this->pointData.data.x, this->pointData.data.y, this->pointData.data.z);

		glLineWidth(10.0f);
		
		glColor3f(1.0f, 1.0f, 1.0f);

		//Bottom Line
		glBegin(GL_LINES);
		glVertex3f(orgin.x, orgin.y, orgin.z);
		glVertex3f(orgin.x+0.2f, orgin.y, orgin.z);
		glEnd();
		//Middle Line
		glBegin(GL_LINES);
		glVertex3f(orgin.x+0.1f, orgin.y, orgin.z);
		glVertex3f(orgin.x + 0.1f, orgin.y+0.4f, orgin.z);
		glEnd();
		//Top Line
		glBegin(GL_LINES);
		glVertex3f(orgin.x, orgin.y + 0.4f, orgin.z);
		glVertex3f(orgin.x + 0.2f, orgin.y + 0.4f, orgin.z);
		glEnd();

		
	}
	else if (this->type == GameObject::LETTERO) {
		glm::vec3 orgin = glm::vec3(this->pointData.data.x, this->pointData.data.y, this->pointData.data.z);

		glLineWidth(10.0f);

		glColor3f(1.0f, 1.0f, 1.0f);

		//bottom
		glBegin(GL_LINES);
		glVertex3f(orgin.x, orgin.y, orgin.z);
		glVertex3f(orgin.x + 0.2f, orgin.y, orgin.z);
		glEnd();
		//right
		glBegin(GL_LINES);
		glVertex3f(orgin.x + 0.2f, orgin.y, orgin.z);
		glVertex3f(orgin.x + 0.2f, orgin.y+0.2f, orgin.z);
		glEnd();
		//top
		glBegin(GL_LINES);
		glVertex3f(orgin.x, orgin.y + 0.2f, orgin.z);
		glVertex3f(orgin.x + 0.2f, orgin.y + 0.2f, orgin.z);
		glEnd();
		//left
		glBegin(GL_LINES);
		glVertex3f(orgin.x, orgin.y + 0.2f, orgin.z);
		glVertex3f(orgin.x, orgin.y, orgin.z);
		glEnd();
	}
	else if (this->type == GameObject::FIVESHAPE){
		glColor3f(this->color.x, this->color.y, this->color.z);
		glBegin(GL_TRIANGLE_FAN);

		glVertex3f(this->fiveshapeData.firstPoint.x, this->fiveshapeData.firstPoint.y, this->fiveshapeData.firstPoint.z);
		glVertex3f(this->fiveshapeData.secondPoint.x, this->fiveshapeData.secondPoint.y, this->fiveshapeData.secondPoint.z);
		glVertex3f(this->fiveshapeData.thirdPoint.x, this->fiveshapeData.thirdPoint.y, this->fiveshapeData.thirdPoint.z);
		glVertex3f(this->fiveshapeData.fourthPoint.x, this->fiveshapeData.fourthPoint.y, this->fiveshapeData.fourthPoint.z);
		glVertex3f(this->fiveshapeData.fifthPoint.x, this->fiveshapeData.fifthPoint.y, this->fiveshapeData.fifthPoint.z);

		glEnd();
	}
	else {
		Console_OutputLog(L"Render Function Not Set!", LOGINFO);
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


