#ifndef GENERAL_H
#define GENERAL_H

#include "Global.h"
#include "raylib.h"

float abs(const Vector2& vector);

Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& vector, const float& x);
Vector2 operator*(const float& x, const Vector2& vector);
Vector2 operator/(const Vector2& vector, const float& x);

Color operator+(const Color& x, const Color& y);
Color operator*(Color color, const float& x);
Color operator*(const float& x, Color color);
Color to_color(const float& x);

float to_float(const Color& color);

bool operator==(const Vector2& a, const Vector2& b);
bool operator!=(const Vector2& a, const Vector2& b);

bool operator==(const Color& a, const Color& b);
bool operator!=(const Color& a, const Color& b);

int to_int(const std::string& str);

float arctan(const Vector2& vector);
float to_degree(const float& radian);
float TransX(const float& x);
float TransY(const float& y);

Vector2 Trans(const Vector2& vector);
Vector2 TransToGlobalPoint(const Camera2D& camera, const Vector2& point);
Vector2 TransToCameraPoint(const Camera2D& camera, const Vector2& point);

Vector2 getCenter(const Vector2& a, const Vector2& b, const float& angular);

Rectangle TransToCameraRec(const Camera2D& camera, Rectangle rec);

string readFromFile(const string& link);
vector<string> readFromFileStr(const string& link);
vector<int> readFromFileInt(const string& link);

vector<string> split(const string& str);

namespace MyBase {
    Vector2 getWindowSize();
    std::string toString(const Vector2& vector);
}
#endif