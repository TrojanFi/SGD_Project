#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
class Vector2D
{

public:
	float X, Y;

public:
	Vector2D(float x=0, float y=0): X(x), Y(y) {}

public:
	inline Vector2D operator+(const Vector2D v2) const {
		return Vector2D(X + v2.X, Y + v2.Y);
	}

	inline Vector2D operator-(const Vector2D v2) const {
		return Vector2D(X - v2.X, Y - v2.Y);
	}

	inline Vector2D operator*(const Vector2D v2) const {
		return Vector2D(X * v2.X, Y * v2.Y);
	}

	void Log(std::string mag = "") {
		std::cout << mag << "(X  Y) = (" << X << " " << Y << ")" << std::endl;
	}
private:
	//v3.x = v1.x + v2.x;
	//v3.y = v1.y + v2.y;

};


#endif // !1
