/**
 * @file main.cpp
 * @brief Entry point for rendering a 3D scene using the ray tracer.
 *
 * This file sets up the world, materials, objects, and camera parameters,
 * then renders the final image by tracing rays through the scene.
 */

#include "constants.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "color.h"

/**
 * @brief Computes the intersection between a ray and a sphere.
 *
 * Solves the quadratic equation for the intersection points of a ray and a sphere.
 *
 * Equation: |r(t) - C|² = R²
 * 
 * @param center Center of the sphere.
 * @param radius Radius of the sphere.
 * @param r Incoming ray.
 * @return Distance t to the closest intersection point, or -1.0 if no intersection occurs.
 */
double hit_sphere(const point3 &center, double radius, const ray &r)
{
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0)
        return -1.0; // No intersection

    // Return nearest valid intersection point
    return (h - std::sqrt(discriminant)) / a;
}

/**
 * @brief Program entry point.
 *
 * Builds a random 3D scene consisting of diffuse, metal, and glass spheres
 * over a large ground plane, sets up a camera with depth of field, and renders
 * the scene using path tracing.
 */
int main()
{
    hittable_list world;

    // Ground plane (large sphere under the scene)
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    // Generate random small spheres
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            // Ensure spheres don't overlap with the main center area
            if ((center - point3(4, 0.2, 0)).length() > 0.9)
            {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // Diffuse (Lambertian)
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // Metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // Glass (Dielectric)
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    // Three main large spheres
    auto material1 = make_shared<dielectric>(1.5);             // Glass sphere
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1)); // Diffuse sphere
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0); // Mirror-like sphere
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    // Camera setup
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth = 10;

    // Camera position and orientation
    cam.vfov = 20;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    // Depth of field configuration
    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    // Render the final image
    cam.render(world);
}
