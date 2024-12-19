#pragma once
#include "ClassBase.h"
#include "../HitLa/Hit.h"
class Material
{
public:
    virtual ~Material() = default;
    virtual bool scatter(  const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const
    {
        return false;
    }
};



class lambertian : public Material
{
private:
    Color albedo;
public:
    lambertian(const Color& a) : albedo(a) {}
    bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const override
    {
        auto scatter_direction=rec.normal+random_unit_vector();

        if (scatter_direction.near_zero())
            scatter_direction=rec.normal;
    
        scattered=Ray(rec.point, scatter_direction);
        attenuation=albedo;
        return true;
    }
};


class Metal : public Material
{
private:
    Color albedo;
    double fuzz;
public:
    Metal(const Color& a, double fuzz ) : albedo(a),fuzz(fuzz) {}
    bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const override
    {
        Vec3 reflected=reflect(r_in.direction, rec.normal);
        reflected=reflected.normalize()+fuzz*random_unit_vector();
        scattered=Ray(rec.point, reflected);
        attenuation=albedo;
        return (dot(scattered.direction, rec.normal)>0);
    }
};