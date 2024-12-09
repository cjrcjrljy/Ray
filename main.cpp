#include"ClassBase/ClassBase.h"
#include<iostream>

#include "ClassBase/Camera.h"
#include"HitLa/Hit.h"
using namespace std;
Color ray_color(const Ray& r) {
	Vec3 unit_direction = r.direction.normalize();
	auto a = 0.5*(unit_direction.y + 1.0);
	return Color(1.0, 1.0, 1.0)*(1.0-a) + Color(0.5, 0.7, 1.0)*a;
}

int main() {

	// Image

	
	Vec3 Sp(0,0,-1);	
	double Sp_r=0.6;
	Sphere sphere(Sp,Sp_r);
	Hittable_list world;
	world.add(make_shared<Sphere>(point3(0,0,-1), 0.5));
	world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));
	

	
	// Calculate the image height, and ensure that it's at least 1.


	
	// Render
	ofstream fout("output.ppm");
	Camera camera;
	camera.aspect_ratio=16.0 / 9.0;
	camera.image_width=640;
	camera.render(world,fout);
	
}
