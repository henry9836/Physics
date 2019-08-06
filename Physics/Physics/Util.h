#pragma once

struct Vector3 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	inline Vector3(void) {

	}

	inline Vector3(const float x, const float y, const float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline Vector3 operator - (Vector3 B) {
		return Vector3{ x - B.x, y - B.y, z - B.z };
	};

	inline Vector3 operator + (Vector3 B) {
		return Vector3{ x + B.x, y + B.y, z + B.z };
	};

	inline Vector3 operator / (Vector3 B) {
		return Vector3{ x / B.x, y / B.y, z / B.z };
	};

	inline Vector3 operator * (float B) {
		return Vector3{ x * B, y * B, z * B };
	}

	inline bool operator != (Vector3 B) {
		if (x != B.x || y != B.y || z != B.z) {
			return true;
		}
		return false;
	}

	inline bool operator == (Vector3 B) {
		if (x != B.x || y != B.y || z != B.z) {
			return false;
		}
		return true;
	}

};

struct Vector2 {
	float x = 0.0f;
	float y = 0.0f;
};

struct IntVector2 {
	int x = 0;
	int y = 0;
};

struct TriangleData {
	Vector3 firstPoint =  { -9999, -9999, 0 };
	Vector3 secondPoint = { -9999, -9999, 0 };
	Vector3 thirdPoint =  { -9999, -9999, 0 };
};

struct LineData {
	Vector3 firstPoint =  { -9999, -9999, 0 };
	Vector3 secondPoint = { -9999, -9999, 0 };
};
