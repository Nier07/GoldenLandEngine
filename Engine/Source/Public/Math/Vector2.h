#pragma once

struct Vector2 {
	// simple constructor
	Vector2() : x(0.0f), y(0.0f) {};

	// assigned constructor
	Vector2(float x, float y) : x(x), y(y) {};

	// uniform constructor
	Vector2(float uniform) : x(uniform), y(uniform) {};

	~Vector2() = default;

	// Operators
	
	// vector 2 assignment operator
	Vector2& operator=(const Vector2& Other) {
		x = Other.x;
		y = Other.y;

		return *this;
	}

	// boolean operators
	// equal
	bool operator==(const Vector2& Other) {
		return x == Other.x && y == Other.y;
	}

	// not equal
	bool operator!=(const Vector2& Other) {
		return x != Other.x && y != Other.y;
	}

	// arithmatic operators
	// addition
	Vector2 operator+(const Vector2& Other) {
		return Vector2(Other.x + x, Other.y + y);
	}
	// addition equals
	Vector2& operator+=(const Vector2& Other) {
		return *this = *this + Other;
	}

	// subtraction
	Vector2 operator-(const Vector2& Other) {
		return Vector2(x - Other.x, y - Other.y);
	}
	// subtraction equals
	Vector2& operator-=(const Vector2& Other) {
		return *this = *this - Other;
	}

	// multiply vector2 by vector2
	Vector2 operator*(const Vector2& Other) {
		return Vector2(x * Other.x, y * Other.y);
	}
	// multiply equals vector2 by vector2
	Vector2& operator*=(const Vector2& Other) {
		return *this = *this * Other;
	}
	// multiply vector2 by scalar
	Vector2 operator*(const float& Scalar) {
		return Vector2(x * Scalar, y * Scalar);
	}
	// multiply equals vector2 by scalar
	Vector2& operator*=(const float& Scalar) {
		return *this = *this * Scalar;
	}

	// division vector2 by vector2
	Vector2 operator/(const Vector2& Other);
	// division equals vector2 by vector2
	Vector2& operator/=(const Vector2& Other);
	// division vector2 by scalar
	Vector2 operator/(const float& Scalar);
	// division equals vector2 by scalar
	Vector2& operator/=(const float& Scalar);

	// return an infinate negative vector / invalid vector
	static Vector2 NaN();

	// get squared length / magnitude / size of vector2
	// inaccurate by double the size but cheap
	float LengthSqd() {
		return x * x + y * y;
	}
	// get the acutal length / magnitude / size of vector2
	float Length();

	// get the distance between 2 vector2's
	static float DistSqd(Vector2& V1, Vector2& V2) {
		Vector2 DistanceVector(V1 - V2);

		return DistanceVector.x * DistanceVector.x + DistanceVector.y * DistanceVector.y;
	}
	// get actual distance between 2 vector2's
	static float Distance(Vector2& V1, Vector2& V2);

	// log the vector to the console
	void Log();
	//l log the length of the vector2 to the console
	void LogLength();

	float x, y;
};