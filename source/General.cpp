#include "../include/General.h"

float abs(const Vector2& vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
};

Vector2 operator+(const Vector2& a, const Vector2& b) {
    return { a.x + b.x, a.y + b.y };
};
Vector2 operator-(const Vector2& a, const Vector2& b) {
    return { a.x - b.x, a.y - b.y };
};
Vector2 operator*(const Vector2& vector, const float& x) {
    return { x * vector.x, x * vector.y };
};
Vector2 operator*(const float& x, const Vector2& vector) {
    return { x * vector.x, x * vector.y };
};
Vector2 operator/(const Vector2& vector, const float& x) {
    return { vector.x / x, vector.y / x };
}
Color operator+(const Color& x, const Color& y) {
    Color ans;
    ans.a = x.a + y.a*(255-x.a)/255;
    ans.r = (x.r*x.a + y.r*y.a*(255-x.a)/255)/ans.a;
    ans.g = (x.g*x.a + y.g*y.a*(255-x.a)/255)/ans.a;
    ans.b = (x.b*x.a + y.b*y.a*(255-x.a)/255)/ans.a;
    return ans;
}
Color operator*(Color color, const float& x) {
    color.a*=x;
    return color;
}
Color operator*(const float& x, Color color) {
    color.a*=x;
    return color;
}

bool operator==(const Vector2& a, const Vector2& b) {
    return a.x == b.x && a.y == b.y;
}
bool operator!=(const Vector2& a, const Vector2& b) {
    return a.x != b.x || a.y != b.y;
}
bool operator!=(const Color& a, const Color& b) {
    return a.r != b.r || a.b!=b.b || a.g != b.g || a.a != b.a;
}
bool operator==(const Color& a, const Color& b) {
    return a.r == b.r && a.g == b.g && a.b==b.g && a.a==b.a;
}

float arctan(const Vector2 &vector) {
    float ans = atan(vector.y/vector.x);
    if (vector.x < 0) ans+=M_PI;
    return ans;
}
float to_degree(const float& radian) {
    return radian/M_PI*180;
}

int to_int(const std::string& str) {
    int ans = 0;
    for (int i = 0; i < str.size(); i++) {
        if (std::isdigit(str[i])) ans = ans * 10 + str[i] - '0';
    }
    return ans;
}

Vector2 getCenter(const Vector2& a, const Vector2& b, const float& angular) {
    Vector2 middle = (a+b)/2;
    Vector2 u = {middle.y, -middle.x};
    float radius = abs(b-a)/angular;
    float side = abs(b-a)/2;
    side = sqrt(radius*radius - side*side);
    return middle + u/side*radius;
}

Rectangle TransToCameraRec(const Camera2D& camera, Rectangle rec) {
    rec.x = camera.offset.x + rec.x * camera.zoom;
    rec.y = camera.offset.y + rec.y * camera.zoom;
    rec.width *= camera.zoom;
    rec.height *= camera.zoom;
    return rec;
}
Vector2 TransToGlobalPoint(const Camera2D& camera, const Vector2& point) {
    return (point - camera.offset) / camera.zoom;
}
string readFromFile(const string& link) {
    string ans;
    ifstream fin(link);
    string line;
    while (!fin.eof()) {
        getline(fin, line);
        ans += line + '\n';
    }
    fin.close();
    return ans;
}
vector<string> readFromFileStr(const string& link) {
    vector<string> ans;
    ifstream fin(link);
    while (!fin.eof()) {
        ans.push_back("");
        getline(fin, ans.back());
    }
    ans.pop_back();
    fin.close();
    return ans;
}
vector<int> readFromFileInt(const string& link) {
    vector<int> ans;
    ifstream fin(link);
    while (!fin.eof()) {
        ans.push_back(0);
        fin >> ans.back();
    }
    ans.pop_back();
    fin.close();
    return ans;
}
vector<string> split(const string& str) {
    vector<string> ans = {""};
    for (char c:str) {
        if ((c==' ' || c=='\n') && ans.back().size()) ans.push_back("");
        else ans.back().push_back(c);
    }
    return ans;
}