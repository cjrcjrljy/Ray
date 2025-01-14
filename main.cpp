#include"ClassBase/ClassBase.h"
#include<iostream>
#include "Uitils/uitils.h"
#include "ClassBase/Camera.h"
#include"HitLa/Hit.h"
using namespace std;
Color ray_color(const Ray& r) {
	Vec3 unit_direction = r.direction.normalize();
	auto a = 0.5*(unit_direction.y + 1.0);
	return Color(1.0, 1.0, 1.0)*(1.0-a) + Color(0.5, 0.7, 1.0)*a;
}

int main() {
    Hittable_list world;
    ofstream fout("output.ppm");
    auto ground_material = make_shared<lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -2; a < 2; a++) {
        for (int b = -2; b < 2; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Vec3::random() * Vec3::random();
                    Color col;
                    col.r = albedo.x;
                    col.g = albedo.y;
                    col.b = albedo.z;
                    sphere_material = make_shared<lambertian>(col);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Vec3::random(0.5, 1);
                    Color col;
                    col.r = albedo.x;
                    col.g = albedo.y;
                    col.b = albedo.z;
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(col, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 900;
    cam.samples_per_pixel = 10;
    cam.max_depth         = 5;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.render(world,fout);
}