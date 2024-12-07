#include"ClassBase/ClassBase.h"
#include<iostream>
#include"HitLa/Hit.h"
using namespace std;
Color ray_color(const Ray& r) {
	Vec3 unit_direction = r.direction.normalize();
	auto a = 0.5*(unit_direction.y + 1.0);
	return Color(1.0, 1.0, 1.0)*(1.0-a) + Color(0.5, 0.7, 1.0)*a;
}

int main() {

	// Image

	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 800;

	// Calculate the image height, and ensure that it's at least 1.
	int image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// Camera

	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width)/image_height);
	auto camera_center = Vec3(0, 0, 0);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	auto viewport_u = Vec3(viewport_width, 0, 0);//3.55555
	auto viewport_v = Vec3(0, -viewport_height, 0);//2

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	auto pixel_delta_u = viewport_u / image_width;//每个点之间的间隔
	auto pixel_delta_v = viewport_v / image_height;

	// Calculate the location of the upper left pixel.
	auto viewport_upper_left = camera_center
							 - Vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
	auto pixel00_loc = viewport_upper_left +  (pixel_delta_u + pixel_delta_v)*0.5 ;

	Vec3 Sp(0,0,-1);	
	double Sp_r=0.6;
	
	// Render
	ofstream fout("output.ppm");
	fout << "P3\n" << image_width << " " << image_height << "\n255\n";
	double maxx=1;
	for (int j = 0; j < image_height; j++) {
		// std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto pixel_center = pixel00_loc + ( pixel_delta_u*i) + ( pixel_delta_v*j);
			auto ray_direction = pixel_center - camera_center;
			Ray r(camera_center, ray_direction);
			double tt =HitSprehe(r,Sp,Sp_r); 
			if (tt)
			{
				Vec3 point=r.at(tt);
				point=point.normalize();
				write_color(fout,Color(point.x,point.y,point.z));
				continue;
			}
			Color pixel_color = ray_color(r);
			write_color(fout, pixel_color);
		}
	}
	std::clog << "\rDone.                 \n";

}