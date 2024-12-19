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
	static Vec3 random();
	static Vec3 random(double min, double max);
	
	template<typename T>
	friend  Vec3 operator*(T t, const Vec3& v)
	{
		return Vec3(v.x*t, v.y*t, v.z*t);
	}
	bool near_zero() const {
		// Return true if the vector is close to zero in all dimensions.
		auto s = 1e-8;
		return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
	}
	inline Vec3 random_unit_vector() {
		while (true) {
			auto p = Vec3::random(-1,1);
			auto lensq = p.length()*p.length();
			if (1e-160 < lensq && lensq <= 1)
				return p / sqrt(lensq);
		}
	}

	
};
double dot(const Vec3& v1, const Vec3& v2);
Vec3 cross(const Vec3& v1, const Vec3& v2);

inline Vec3 random_unit_vector() {
	while (true) {
		auto p = Vec3::random(-1,1);
		auto lensq = p.length()*p.length();
		if (1e-160 < lensq && lensq <= 1)
			return p / sqrt(lensq);
	}
}
inline Vec3 random_on_hemisphere(const Vec3& normal) {
	Vec3 on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return on_unit_sphere;
	else
		return on_unit_sphere*-1;
}
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
	Color& operator+=(const Color& c);
	friend  Color operator*(int t,const Color &color )
	{
		Color *re=new Color();
		re->b=color.b*t;
		re->g=t*color.g;
		re->r=t*color.r;
		return *re;
		// return Color(t*color.r,t*color.g,t*color.b);
	}
	friend  Color operator*(double t,const Color &color )
	{
		Color *re=new Color();
		re->b=color.b*t;
		re->g=t*color.g;
		re->r=t*color.r;
		return *re;
		// return Color(t*color.r,t*color.g,t*color.b);
	}
	friend  Color operator*(float t,const Color &color )
	{
		Color *re=new Color();
		re->b=color.b*t;
		re->g=t*color.g;
		re->r=t*color.r;
		return *re;
		// return Color(t*color.r,t*color.g,t*color.b);
	}
	friend  Color operator*(Color t,const Color &color )
	{
		Color *re=new Color();
		re->b=color.b*t.b;
		re->g=t.g*color.g;
		re->r=t.r*color.r;
		return *re;
		// return Color(t*color.r,t*color.g,t*color.b);
	}
};
inline double linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return std::sqrt(linear_component);

	return 0;
}
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

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2*dot(v,n)*n;
}

