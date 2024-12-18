#pragma once
#include "ClassBase.h"
#include"../Uitils/uitils.h"
#include"../HitLa/Hit.h"
class Camera
{
public:
    double aspect_ratio=1.0;
    int image_width=100;
    int    samples_per_pixel = 10;

    
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
                    pixel_color+=rayColor(ray, world);
                    
                }
                
                write_color(outf, pixel_samples_scale*pixel_color);
            }
        }
    }

    Color rayColor(const Ray& ray,const Hitobjects &world)
    {
        Hit_record rec;
        if (world.hit(ray,0,infinity,rec))
        {
            Vec3 color=rec.normal+Vec3(1)*0.5;
            return Color( color.x,color.y,color.z);
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
        center=point3(0,0,0);

        double focal_length=1.0;
        double viewport_height=2.0;
        double viewport_width=viewport_height*(double(image_width)/image_height);
        Vec3 viewport_u=Vec3(viewport_width,0,0);
        Vec3 viewport_v=Vec3(0,-viewport_height,0);

        pixel_delta_u=viewport_u/image_width;
        pixel_delta_v=viewport_v/image_height;

        auto viewport_upper_left= center - Vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left +(pixel_delta_u + pixel_delta_v)*0.5;
        
    }




    Ray get_ray(int j, int i) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((j + offset.x) * pixel_delta_u)
                          + ((i + offset.y) * pixel_delta_v);

        auto ray_origin = center;
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
};
