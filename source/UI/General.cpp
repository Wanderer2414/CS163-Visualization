#include "General.h"
#include "raylib.h"

extern Vector2 WindowSize;

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
Color to_color(const float &x) {
    Color color;
    memcpy(&color,&x, 4);
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

int to_int(const std::string& str) {
    int ans = 0;
    for (int i = 0; i < str.size(); i++) {
        if (std::isdigit(str[i])) ans = ans * 10 + str[i] - '0';
    }
    return ans;
}

float arctan(const Vector2 &vector) {
    float ans = atan(vector.y/vector.x);
    if (vector.x < 0) ans+=M_PI;
    return ans;
}
float to_degree(const float& radian) {
    return radian/M_PI*180;
}
float to_float(const Color& color) {
    float x;
    memcpy(&x, &color, 4);
    return x;
}

float TransX(const float& x) {
    return x/1366*WindowSize.x;
}

float TransY(const float& y) {
    return y/700*WindowSize.y;
}

Vector2 Trans(const Vector2& vector) {
    return {TransX(vector.x), TransY(vector.y)};
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

Vector2 TransToCameraPoint(const Camera2D& camera, const Vector2& point) {
    return point*camera.zoom + camera.offset;
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
        if (c==' ' || c=='\n') {
           if (ans.back().size()) ans.push_back("");
        }
        else ans.back().push_back(c);
    }
    if (ans.back().empty()) ans.pop_back();
    return ans;
}
namespace MyBase {
    Vector2 getWindowSize() {
        #ifdef __linux__
        using namespace XL;
        XL::Display* display = XL::XOpenDisplay(NULL);
        if (!display) {
            std::cerr << "Cannot open display\n";
            exit(0);
        }
        XL::Screen* screen = ScreenOfDisplay(display, 0);
        float x = screen->width, y = screen->height;
        XCloseDisplay(display);
        return {x, y-40.f/1010*y};
        #endif

        #ifdef _WIN32
        SetProcessDPIAware();
        int width = GetSystemMetrics(SM_CXSCREEN);
        int height = GetSystemMetrics(SM_CYSCREEN);
        std::cout << width << " " << height << std::endl;
        return {width, height-40.f/1010*height};
        #endif
    }
    std::string toString(const Vector2& vector) {
        return TextFormat("{%.f,%.f}", vector.x, vector.y);
    }
}