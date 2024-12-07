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

// double HitSprehe(const Ray r, Vec3 Sp_ori, double Sp_r) {  
//     Vec3 oc = r.origin - Sp_ori;  
//     double a = dot(r.direction, r.direction);  
//     double b = 2.0 * dot(oc, r.direction);  
//     double c = dot(oc, oc) - Sp_r * Sp_r;  
//     
//     double discriminant = b*b - 4*a*c;  
//     
//     if (discriminant < 0) {  
//         return 0; // 没有交点  
//     }   
//     
//     // 计算两个交点的时间  
//     double t1 = (-b - sqrt(discriminant)) / (2.0*a);  
//     double t2 = (-b + sqrt(discriminant)) / (2.0*a);  
//     
//     // 返回最近的正交点时间  
//     if (t1 > 0) return t1;  
//     if (t2 > 0) return t2;  
//     
//     return 0; // 没有正交点  
// }
