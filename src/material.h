/**
 * @file material.h
 * @brief Defines material classes that control how rays interact with surfaces.
 *
 * Each material type determines how an incoming ray scatters, reflects, or refracts
 * when it hits an object. This forms the basis of realistic lighting and shading.
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "hittable.h"

/**
 * @class material
 * @brief Abstract base class representing surface materials.
 *
 * The `scatter` function defines how a ray interacts with the surface.
 * It computes a scattered ray and determines the light attenuation.
 */
class material
{
public:
    virtual ~material() = default;

    /**
     * @brief Determines how an incoming ray scatters upon hitting the surface.
     *
     * @param r_in Incoming ray.
     * @param rec Intersection information (hit point, normal, etc.).
     * @param attenuation Color attenuation of the scattered ray.
     * @param scattered Output scattered ray.
     * @return True if the ray is scattered, false otherwise.
     */
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
    {
        return false;
    }
};

/**
 * @class lambertian
 * @brief Represents a diffuse (matte) material.
 *
 * Scatters rays randomly in directions close to the surface normal,
 * simulating rough, non-shiny surfaces.
 *
 * Formula: scatter direction = normal + random_unit_vector()
 */
class lambertian : public material
{
public:
    lambertian(const color &albedo) : albedo(albedo) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        vec3 scatter_direction = rec.normal + random_unit_vector();

        // Handle the rare case of zero scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo; ///< Surface color (fraction of light reflected)
};

/**
 * @class metal
 * @brief Represents a reflective metallic material.
 *
 * Reflects incoming rays based on the surface normal, with optional fuzziness.
 * 
 * Formula: reflected = unit_vector(reflect(direction, normal)) + fuzz * random_unit_vector()
 */
class metal : public material
{
public:
    metal(const color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit_vector(reflected) + fuzz * random_unit_vector();
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

private:
    color albedo; ///< Surface color (light reflectance)
    double fuzz;  ///< Roughness factor (0 = perfect mirror, 1 = very rough)
};

/**
 * @class dielectric
 * @brief Represents a transparent material (like glass or water).
 *
 * Handles both reflection and refraction using Snell’s law and
 * Schlick’s approximation for reflectance.
 */
class dielectric : public material
{
public:
    explicit dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        attenuation = color(1.0, 1.0, 1.0); // No color loss
        double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1 - cos_theta * cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;

        // Reflect or refract based on total internal reflection or reflectance probability
        if (cannot_refract || reflectance(cos_theta, ri) > random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, ri);

        scattered = ray(rec.p, direction);
        return true;
    }

private:
    double refraction_index; ///< Material’s refractive index (e.g., glass ≈ 1.5)

    /**
     * @brief Schlick’s approximation for reflectance.
     *
     * Reflectance ≈ R₀ + (1 - R₀)(1 - cosθ)⁵
     */
    static double reflectance(double cosine, double refraction_index)
    {
        double r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 *= r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};

#endif // MATERIAL_H
