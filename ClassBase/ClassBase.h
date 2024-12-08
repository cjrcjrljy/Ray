#pragma once
#include<cmath>
#include<ostream>
#include<iostream>
#include<fstream>
using namespace std;

class Vec3 {

public:
	double x, y, z;
	double e[3] = { x, y, z };
	template<typename T>
	Vec3(T t):x(t),y(t),z(t){}
	Vec3() : x(0), y(0), z(0) {}
	Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
	Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
	Vec3 operator+(const Vec3& v) const;
	Vec3 operator-(const Vec3& v) const;
	Vec3 operator*(int T) const;
	Vec3 operator*(double T) const;
	double length() const;
	Vec3 normalize() const;
	Vec3 operator/(double T) const;
	Vec3 operator/(int T) const;
	
};
double dot(const Vec3& v1, const Vec3& v2);
Vec3 cross(const Vec3& v1, const Vec3& v2);


typedef Vec3 point3;
class Color {
public:
	double r, g, b;//r,b,g values are between 0 and 1
	Color() : r(0), g(0), b(0) {}
	Color(double r, double g, double b) : r(r), g(g), b(b) {}
	Color(Vec3 p) : r(p.x), g(p.y), b(p.z) {}
	Color(const Vec3& p) : r(p.x), g(p.y), b(p.z) {}
	Color operator+(const Color& c) const;
	Color operator-(const Color& c) const;
	Color operator*(double T) const;
	Color operator/(double T) const;
	Color operator/(int T) const;
	Color operator*(int T) const;
	
};

void write_color(ostream& out, Color pixel_color);


class Ray
{

public:
	Vec3 origin, direction;
	Ray() : origin(0, 0, 0), direction(0, 1, 0) {}
	Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}
	Vec3 at(double t) const;
};

class Point
{
public:
	Vec3 origin;
	Vec3 normal;
	Point () : origin(0, 0, 0), normal(0, 0, 0) {}
	Point(const Vec3& origin, const Vec3& normal) : origin(origin), normal(normal) {}
};


