#include "Hit.h"

double HitSprehe(const Ray r, Vec3 Sp_ori, double Sp_r)
{
    Vec3 Line_r_s=Sp_ori-r.origin;
    double Line_r=dot(Line_r_s,r.direction)/r.direction.length();
    double Line__r=Line_r_s.length();
    double dis=Line__r*Line__r-Line_r*Line_r;
    double Sp_r_2=Sp_r*Sp_r;
    if (dis<=Sp_r_2)
    {
        Vec3 ray_dir=r.direction;
        Vec3 ray_origin=r.origin;
        double A=dot(ray_dir,ray_dir);
        double B=2*dot(ray_dir,ray_origin-Sp_ori);
        double C=dot(ray_origin-Sp_ori,ray_origin-Sp_ori);
        double delta=B*B-A*C;
        double t1=(-B+sqrt(delta))/(2*A);
        double t2=(-B-sqrt(delta))/(2*A);
        return min(t1,t2);
     
    }
    return 0;
    
}

