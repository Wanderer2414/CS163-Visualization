#include "../include/General.h"
#include <cctype>
#include <cmath>
#include <string>

using namespace std;
float abs(const Vector2& vector) {
    return sqrt(vector.x*vector.x + vector.y*vector.y);
};

Vector2 operator+(const Vector2& a, const Vector2& b) {
    return {a.x + b.x, a.y+b.y};
};
Vector2 operator-(const Vector2& a, const Vector2& b) {
    return {a.x - b.x, a.y - b.y};
};
Vector2 operator*(const Vector2& vector, const float& x) {
    return {x*vector.x, x*vector.y};
};
Vector2 operator*(const float& x, const Vector2& vector) {
    return {x*vector.x, x*vector.y};
};
Vector2 operator/(const Vector2& vector, const float& x) {
    return {vector.x/x, vector.y/x};
}

bool operator==(const Vector2& a, const Vector2& b) {
    return a.x==b.x && a.y==b.y;
}
bool operator!=(const Vector2& a, const Vector2& b) {
    return a.x!=b.x || a.y!=b.y;
}

int to_int(const std::string& str) {
    int ans = 0;
    for (int i = 0; i<str.size(); i++) {
        if (std::isdigit(str[i])) ans = ans*10 + str[i]-'0';
    }
    return ans;
} 