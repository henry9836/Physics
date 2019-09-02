#include "Physics.h"

#define PI 3.141592654f

float dotproduct(Vector3 VECA, Vector3 VECB)
{
	float product = 0;
	product += VECA.x * VECB.x;
	product += VECA.y * VECB.y;
	product += VECA.z * VECB.z;
	return (product);
}

vector<float> mutiplay(float times, vector<float> OG)
{
	vector<float>ans = { 0,0,0 };

	for (int i = 0; i < 3; i++)
	{
		ans.at(i) = OG.at(i) * times;
	}
	return (ans);
}

Vector3 vsubtract(Vector3 first, Vector3 second)
{
	first.x = first.x - second.x;
	first.y = first.y - second.y;
	first.z = first.z - second.z;
	return(first);
}

void TrianglePlaneFunction(Vector3 plane, Vector3 planeNormal, TriangleData Triangle)
{

	float ans1 = dotproduct(planeNormal, vsubtract(plane, Triangle.firstPoint)) / dotproduct(planeNormal, vsubtract(Triangle.secondPoint, Triangle.firstPoint));
	float ans2 = dotproduct(planeNormal, vsubtract(plane, Triangle.secondPoint)) / dotproduct(planeNormal, vsubtract(Triangle.thirdPoint, Triangle.secondPoint));
	float ans3 = dotproduct(planeNormal, vsubtract(plane, Triangle.thirdPoint)) / dotproduct(planeNormal, vsubtract(Triangle.firstPoint, Triangle.thirdPoint));
	vector<float>anspool{ ans1, ans2, ans3 };

	bool ans = false;
	for (int i = 0; i < 3; i++)
	{
		if (anspool.at(i) == 0)
		{
			ans = true;
		}
		if (anspool.at(i) == 1)
		{
			ans = true;
		}
		if (anspool.at(i) < 1 && anspool.at(i) > 0)
		{
			ans = true;
		}
	}

	if (ans == true)
	{
		wcout << L"Collision is true" << endl;
	}
	else
	{
		wcout << L"Collision is false" << endl;
	}
}


float LinevPlane(Vector3 planePosition, Vector3 planeNormal, LineData linePositions)
{

	float ans = 0;

	ans = dotproduct(planeNormal, vsubtract(planePosition, linePositions.firstPoint)) / dotproduct(planeNormal, vsubtract(linePositions.secondPoint, linePositions.firstPoint));

	//wcout << ans;

	if (ans == 0)
	{
		wcout << L"intersection at first point" << endl;
	}
	if (ans == 1)
	{
		wcout << L"intersecion at second point" << endl;
	}
	if (ans < 0)
	{
		wcout << L"intersectoin before first point" << endl;
	}
	if (ans > 1)
	{
		wcout << L"intersection beyond second point" << endl;
	}
	if (ans < 1 && ans > 0)
	{
		wcout << L"intersection between the 2 points" << endl;
	}
	else {
		wcout << L"no intersection was found" << endl;
	}
	return ans;
}

void PlanevPoint(Vector3 planePosition, Vector3 planeNormal, Vector3 pointPosition)
{
	float ans = 0;
	float distance = 0;

	distance = dotproduct(planeNormal, planePosition);
	ans = dotproduct(planeNormal, pointPosition) - distance;
	if (ans == 0)
	{
		wcout << L"ON_PLANE" << endl;
	}
	else if (ans < 0)
	{
		wcout << L"BEHIND" << endl;
	}
	else if (ans > 0)
	{
		wcout << L"INFRONT" << endl;
	}
}

Vector3 findPerpendicular(Vector3 pointA, Vector3 pointB) {
	Vector3 dir = pointB - pointA;
	dir = Vector3(dir.y, -dir.x, dir.z);
	float length = sqrt((dir.x * dir.x)+(dir.y * dir.y));
	return Vector3(dir.x/length,dir.y/length,dir.z);
}

glm::vec3 javeLogic(float _angle, float _speed, float _t) {
	glm::vec3 result; //x,y pos, z angle

	float throwAngleRadians = (_angle * PI) / 180.0f;

	result.x = _t * _speed * cos(throwAngleRadians);
	result.y = _t * _speed * sin(throwAngleRadians) - (0.5f * 9.8f * powf(_t, 2));
	result.z = ((atanf(result.x/result.y)) * 180.0f) / PI;

	return result;
}

void javelin() {
	Console_Clear();
	
	float angle, speed, t;
	wcout << " -= Javelin Throw Calculator =- " << endl;

	wcout << L" Throw Angle: ";
	cin >> angle;
	wcout << L" Throw Speed: ";
	cin >> speed;
	wcout << L" Time (-X for steps from start): ";
	cin >> t;
	glm::vec3 tmpRes;
	if (t < 0) {
		t *= -1;
		int max = (int)t;
		t = 1;
		while (t <= max) {
			glm::vec3 oldRes = tmpRes;
			glm::vec3 tmpRes = javeLogic(angle, speed, t);
			if (oldRes != tmpRes) {
				wcout << "--------------------------" << endl << "Time: " << t << endl;
				wcout << "Result: Javelin is at Position(x|y): " << tmpRes.x << "|" << tmpRes.y << " at an angle of: " << tmpRes.z << "Degrees" << endl;
				t++;
			}
			else {
				break;
			}
		}

	}
	else {
		tmpRes = javeLogic(angle, speed, t);
		wcout << "Result: Javelin is at Position(x|y): " << tmpRes.x << "|" << tmpRes.y << " at an angle of: " << tmpRes.z << "Degrees" << endl;
	}

}

bool aboveTarget(float _length, float _angle, float _speed, glm::vec2 _target)
{
	float tAngle = (_angle * PI) / 180.0f;
	float time, rX, rY, h;
	rX = _length * cosf(tAngle);
	rY = _length * sinf(tAngle);

	time = ((_target.x - rX) / ((_speed)* cosf(tAngle)));
	h = rY + (_speed * sinf(tAngle)) * time + (0.5f * -9.8f * powf(time, 2));
	if (h > _target.y)
	{
		return true;
	}
	else
		return false;
}


void cannonAimer() {

	float cannonLength, MuzzleSpeed;
	glm::vec2 target;

	wcout << " -= Cannon Aimer =- " << endl;
	wcout << " Cannon Length: ";
	cin >> cannonLength;
	wcout << " Muzzle Speed: ";
	cin >> MuzzleSpeed;
	wcout << " Target X Position: ";
	cin >> target.x;
	wcout << " Target Y Position: ";
	cin >> target.y;

	float result = -9999;

	for (int i = -900; i <= 900; i++)
	{
		if (aboveTarget(cannonLength, float(i) / 10, MuzzleSpeed, target))
		{
			result = float(i) / 10;
			break;
		}
	}

	if (result == -9999) {
		wcout << "Error: Could not find a valid firing angle!" << endl;
	}
	else {
		wcout << "Firing Angle: " << result << " Degrees" << endl;
	}

}

float sign(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(glm::vec2 pt, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(pt, v1, v2);
	d2 = sign(pt, v2, v3);
	d3 = sign(pt, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

bool PointInTriangleBarycentric(glm::vec2 pt, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3) {

	float a = ((v2.y - v3.y) * (pt.x - v3.x) + (v3.x - v2.x) * (pt.y - v3.y)) / ((v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y));
	float b = ((v3.y - v1.y) * (pt.x - v3.x) + (v1.x - v3.x) * (pt.y - v3.y)) / ((v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y));
	float c = 1 - a - b;

	// p lies in T if and only if 0 <= a <= 1 and 0 <= b <= 1 and 0 <= c <= 1

	if (((0<=a)&&(a<=1))&&((0<=b)&&(b<=1))&&((0<=c)&&(c<=1))) {
		return true;
	}
	return false;
}

glm::vec2 getProj(vector<glm::vec3> shape, glm::vec3 axis) {
	
	Vector3 tmp = Vector3(shape.at(0).x, shape.at(0).y, shape.at(0).z);
	Vector3 axisTmp = Vector3(axis.x, axis.y, axis.z);

	double min = dotproduct(axisTmp, tmp);
	double max = min;

	for (unsigned int i = 1; i < shape.size(); i++) {
		// NOTE: the axis must be normalized to get accurate projections
		Vector3 tmp = Vector3(shape.at(i).x, shape.at(i).y, shape.at(i).z);
		Vector3 axisTmp = Vector3(axis.x, axis.y, axis.z);
		double p = dotproduct(axisTmp, tmp);
		if (p < min) {
			min = p;
		}
		else if (p > max) {
			max = p;
		}
	}


	glm::vec2 proj = glm::vec2(min, max);

	return proj;
}

bool SAT(FivePointShape shape1, FivePointShape shape2) {

	vector<glm::vec3> s1;
	vector<glm::vec3> s2;
	vector<glm::vec3> axis1;
	vector<glm::vec3> axis2;

	s1.push_back(shape1.firstPoint);
	s1.push_back(shape1.secondPoint);
	s1.push_back(shape1.thirdPoint);
	s1.push_back(shape1.fourthPoint);
	s1.push_back(shape1.fifthPoint);
	s2.push_back(shape2.firstPoint);
	s2.push_back(shape2.secondPoint);
	s2.push_back(shape2.thirdPoint);
	s2.push_back(shape2.fourthPoint);
	s2.push_back(shape2.fifthPoint);


	for (size_t i = 0; i < s1.size()-1; i++)
	{
		glm::vec3 p1 = s1[i];
		glm::vec3 p2 = s1[i + 1];

		glm::vec3 edge = p1 - p2;

		glm::vec3 normal = glm::vec3(edge.y, -edge.x, edge.z);

		axis1.push_back(normal);
	}

	for (size_t i = 0; i < s2.size() - 1; i++)
	{
		glm::vec3 p1 = s2[i];
		glm::vec3 p2 = s2[i + 1];

		glm::vec3 edge = p1 - p2;

		glm::vec3 normal = glm::vec3(edge.y, -edge.x, edge.z);

		axis2.push_back(normal);
	}

	for (size_t i = 0; i < axis1.size(); i++)
	{
		glm::vec3 axis = axis1[i];

		//project both shapes
		glm::vec2 proj1 = getProj(s1, axis);
		glm::vec2 proj2 = getProj(s2, axis);

		//if we do not overlap return false
		if ((proj1.x > proj2.y) ||(proj2.x > proj1.y)) {
			return false;
		}
	}

	for (size_t i = 0; i < axis2.size(); i++)
	{
		glm::vec3 axis = axis2[i];

		//project both shapes
		glm::vec2 proj1 = getProj(s1, axis);
		glm::vec2 proj2 = getProj(s2, axis);

		//if we do not overlap return false
		if ((proj1.x > proj2.y) || (proj2.x > proj1.y)) {
			return false;
		}
	}

	return true; //collision detected
}
