#pragma once
#include "../raylib/raylib.h"
#include <cstddef>

float abs(const Vector2& vector);

Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& vector, const float& x);
Vector2 operator*(const float& x, const Vector2& vector);
Vector2 operator/(const Vector2& vector, const float& x);

bool operator==(const Vector2& a, const Vector2& b);
bool operator!=(const Vector2& a, const Vector2& b);