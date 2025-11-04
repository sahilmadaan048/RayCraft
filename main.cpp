#include "constants.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

double hit_sphere(const point3 &center, double radius, const ray &r)
{
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = h * h - a * c;

    // no point of intersecrion
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        // closest intersection point
        return (h - std::sqrt(discriminant)) / a;
    }
}

int main()
{
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(-2, 0, -1), 0.3));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;

    cam.render(world);
}