#include"ClassBase.h"
#include"../Uitils/uitils.h"
Vec3 Vec3::operator+(const Vec3& v) const
{
	Vec3* result = new Vec3();
	result->x = x + v.x;
	result->y = y + v.y;
	result->z = z + v.z;
	return *result;
}

Vec3 Vec3::operator-(const Vec3& v) const
{
	Vec3* result = new Vec3();
	result->x = x - v.x;
	result->y = y - v.y;
	result->z = z - v.z;
	return *result;
}

Vec3 Vec3::operator*(int T) const
{
	Vec3* result = new Vec3();
	result->x = x * T;
	result->y = y * T;
	result->z = z * T;
	return *result;
}

Vec3 Vec3::operator*(double T) const
{
	Vec3* result = new Vec3();
	result->x = x * T;
	result->y = y * T;
	result->z = z * T;
	return *result;
}

double Vec3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalize() const
{
	Vec3* result = new Vec3();
	double len = length();
	result->x = x / len;
	result->y = y / len;

	result->z = z / len;
	return *result;
}

Vec3 Vec3::operator/(double T) const
{
	Vec3* result = new Vec3();
	result->x = x / T;
	result->y = y / T;
	result->z = z / T;
	return *result;
}

Vec3 Vec3::operator/(int T) const
{
	Vec3* result = new Vec3();
	result->x = x / T;
	result->y = y / T;
	result->z = z / T;
	return *result; return Vec3();
}

Vec3 Vec3::random()
{
	return Vec3(random_double() , random_double() , random_double() );
}

Vec3 Vec3::random(double min, double max)
{
	return Vec3(random_double(min,max) ,random_double(min,max),random_double(min,max));
}

double dot(const Vec3& v1, const Vec3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 cross(const Vec3& v1, const Vec3& v2)
{
	Vec3* result = new Vec3();
	result->x = v1.y * v2.z - v1.z * v2.y;
	result->y = v1.z * v2.x - v1.x * v2.z;
	result->z = v1.x * v2.y - v1.y * v2.x;
	return *result;
}

Color Color::operator+(const Color& c) const
{
	Color* result = new Color();
	result->r=r+c.r;
	result->g=g+c.g;
	result->b=b+c.b;
	return *result;
}

Color Color::operator-(const Color& c) const
{
	Color* result = new Color();
	result->r=r-c.r;
	result->g=g-c.g;
	result->b=b-c.b;
	return *result;
}

Color Color::operator*(double T) const
{
	Color* result = new Color();
	result->r=r*T;
	result->g=g*T;
	result->b=b*T;
	return *result;
}

Color Color::operator/(double T) const
{
	Color* result = new Color();
	result->r=r/T;
	result->g=g/T;
	result->b=b/T;
	return *result;
}

Color Color::operator/(int T) const
{
	Color* result = new Color();
	result->r=r/T;
	result->g=g/T;
	result->b=b/T;
	return *result;
}

Color Color::operator*(int T) const
{
	Color* result = new Color();
	result->r=r*T;
	result->g=g*T;
	result->b=b*T;
	return *result;
}

Color& Color::operator+=(const Color& c)
{
	r+=c.r;
	g+=c.g;
	b+=c.b;
	return *this;
}

void write_color(ostream& out, Color pixel_color) {
	auto r = pixel_color.r;
	auto g = pixel_color.g;
	auto b = pixel_color.b;
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);
	// Translate the [0,1] component values to the byte range [0,255].
	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	// Write out the pixel color components.
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

Vec3 Ray::at(double t) const
{
	Vec3* result = new Vec3();
	(*result)=origin+direction*t;
	return *result;
}


