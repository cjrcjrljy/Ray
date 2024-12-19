#pragma once

#include "../ClassBase/ClassBase.h"
class Material;
double HitSprehe(const Ray r,Vec3 Sp_ori,double Sp_r);




class Hit_record
{
public:
    Vec3 point;
    Vec3 normal;
    double t;
    bool front_face;
    shared_ptr<Material> mat;
    void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.
        //
        front_face = dot(r.direction, outward_normal) < 0;
        normal = front_face ? outward_normal : outward_normal*-1;
    }

};

class Hitobjects
{
public:
    virtual ~Hitobjects() = default;

    virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, Hit_record& rec) const = 0;

};



#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class Hittable_list : public Hitobjects {
public:
    std::vector<shared_ptr<Hitobjects>> objects;

    Hittable_list() {}
    Hittable_list(shared_ptr<Hitobjects> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<Hitobjects> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& r, double ray_tmin, double ray_tmax, Hit_record& rec) const override {
        Hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto& object : objects) {
            if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};


class Sphere:public Hitobjects
{
public:
    Vec3 center;
    double radius;
    Sphere(Vec3 center,double radius,shared_ptr<Material> mat):center(center),radius(radius),mat(mat){};
    Sphere():center(Vec3(0,0,0)),radius(0){};
    
    bool hit(const Ray& r, double ray_tmin, double ray_tmax, Hit_record& rec) const override {
        Vec3 oc = center - r.origin;
        auto a = dot (r.direction,r.direction);
        auto h = dot(r.direction, oc);
        auto c = oc.length()*oc.length() - radius*radius;

        auto discriminant = h*h - a*c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root) {
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        rec.t = root;
        rec.point= r.at(rec.t);
        rec.normal = (rec.point - center) / radius;
        rec.mat = mat;
        Vec3 outward_normal = (rec.point - center) / radius;
        
        rec.set_face_normal(r, outward_normal.normalize());
        
        return true;
    }
    shared_ptr<Material> mat;
};