﻿#pragma once
#include "ClassBase.h"
#include "../HitLa/Hit.h"
#include "../Uitils/uitils.h"
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


class dielectric : public Material {
public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered)
    const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;

        vec3 unit_direction = r_in.direction.normalize();
        double cos_theta = std::fmin(dot(unit_direction*-1, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, ri) > random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, ri);

        scattered = Ray(rec.point, direction);
        return true;
    }

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refraction_index;
    static double reflectance(double cosine, double refraction_index) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0*r0;
        return r0 + (1-r0)*std::pow((1 - cosine),5);
    }
};