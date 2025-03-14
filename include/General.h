
#ifndef GENERAL_H
#define GENERAL_H

#include "../raylib/raylib.h"
#include <cstddef>
#include <string>
#include <vector>
using namespace std;
float abs(const Vector2& vector);

Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& vector, const float& x);
Vector2 operator*(const float& x, const Vector2& vector);
Vector2 operator/(const Vector2& vector, const float& x);

bool operator==(const Vector2& a, const Vector2& b);
bool operator!=(const Vector2& a, const Vector2& b);

int to_int(const std::string& str);

Rectangle TransToCameraRec(const Camera2D& camera, Rectangle rec);

vector<string> readFromFileStr(const string& link);
vector<int> readFromFileInt(const string& link);
#endif