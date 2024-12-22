#pragma once
#include "ClassBase.h"
#include"../Uitils/uitils.h"
#include"../HitLa/Hit.h"
#include "Material.h"
class Camera
{
public:
    double aspect_ratio=1.0;
    int image_width=100;
    int    samples_per_pixel = 10;
    int max_depth = 10;
    double vfov = 90;  // Vertical view angle (field of view)
    point3 lookfrom = point3(0,0,0);   // Point camera is looking from
    point3 lookat   = point3(0,0,-1);  // Point camera is looking at
    vec3   vup      = vec3(0,1,0);     // Camera-relative "up" direction
    double defocus_angle = 0;  // Variation angle of rays through each pixel
    double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus
    
    void  render(const Hitobjects &world,ofstream& outf)
    {
        Initialize();
        outf<< "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for(int i=0;i<image_height;i++)
        {
            for(int j=0;j<image_width;j++)
            {
               
               
                Color pixel_color = Color(0,0,0);
                for (int sim=0;sim<samples_per_pixel;sim++)
                {
                    Ray ray =get_ray(j,i);
                    pixel_color+=rayColor(ray, world,max_depth);
                    
                    
                }
                
                write_color(outf, pixel_samples_scale*pixel_color);
            }
        }
    }

    Color rayColor(const Ray& ray,const Hitobjects &world,int depth)
    {
        if (depth<0) return Color(0,0,0);
        Hit_record rec;
        if (world.hit(ray,0.001,infinity,rec))
        {
            // Vec3 color=rec.normal+Vec3(1)*0.5;
            // return Color( color.x,color.y,color.z);
            // Vec3 direction = random_on_hemisphere(rec.normal);
            // Vec3 direction = rec.normal + random_unit_vector();
            // return 0.5 * rayColor(Ray(rec.point, direction), world,depth-1);
       
            Ray scattered;
            Color attenuation;
            if (rec.mat->scatter(ray, rec, attenuation, scattered))
                return attenuation * rayColor(scattered,world ,depth-1);
            return Color(0,0,0);
        }
        Vec3 unit_dir=ray.direction.normalize();
        auto a=0.5*(unit_dir.y+1);
        return  (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
    }

    void Initialize()
    {
        image_height=int(image_width/aspect_ratio);
        image_height=(image_height<1)?1:image_height;
        pixel_samples_scale = 1.0 / samples_per_pixel;
        center = lookfrom;

       
        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2 * h * focus_dist;
        double viewport_width=viewport_height*(double(image_width)/image_height);

        // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
        w = (lookfrom - lookat).normalize();
        u = (cross(vup, w)).normalize();
        v = cross(w, u);

        vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
        vec3 viewport_v = viewport_height * v*-1;  // Vector down viewport vertical ed

        pixel_delta_u=viewport_u/image_width;
        pixel_delta_v=viewport_v/image_height;

        auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left +(pixel_delta_u + pixel_delta_v)*0.5;
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
        
    }


    point3 defocus_disk_sample() const {
        // Returns a random point in the camera defocus disk.
        auto p = random_in_unit_disk();
        return center + (p.x * defocus_disk_u) + (p.y * defocus_disk_v);
    }

    Ray get_ray(int j, int i) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((j + offset.x) * pixel_delta_u)
                          + ((i + offset.y) * pixel_delta_v);

        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

    Vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }


    

private:
    int image_height;
    point3 center;
    point3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
    double pixel_samples_scale;
    vec3   u, v, w;              // Camera frame basis vectors
    vec3   defocus_disk_u;       // Defocus disk horizontal radius
    vec3   defocus_disk_v;       // Defocus disk vertical radius

};
