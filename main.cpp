#include "constants.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

// this function checks if a ray r hits a sphere defined by
// center: the center of the spahere
// radius: the radius of the sphere
/*
    this formula comes on solving the equation of intersection of
    the incident ray and the sphere

    basically all this calculation is needed to find the nearesr point of intersetion of the incident
    ray and the sphere
*/
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

// this function determines the color seen in the direction of ray r
color ray_color(const ray &r, const hittable &world)
{
    /*
        since the camera center is at (0, 0, 0) the sphere center is 1 (focal length) away into  the z axis
        0.5 is the radius of the sphere we have assumed
        r is the incident ray which may intersect the sphere we have deinfed with center (0, 0, -1)
    */
    // auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    // if ray hits the sphere
    // if (t > 0.0)
    // {
    //     // r.at() is the hit point
    //     // vec3(0, 0, -1) is the center of the sphere
    //     vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
    //     return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    // }

    hit_record rec;
    if (world.hit(r, interval(0.001, infinity), rec))
    {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    // else it misses the sphere

    /*
        formula used to create the gradient from Blue color to White
        blendedValue=(1−a)⋅startValue+a⋅endValue
        */

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

/*
    making a ray tracer involves
        1. calculate the ray from the "eye" along a pixel
        2. determine which objects the ray intersects along its way
        3. compute a color of the closest intersection point

    and let's set up a camera to get started
*/

int main()
{

    // Image
    // aspect ration is just = width / height

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // World

    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(-2, 0, -1), 0.3));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta (unit vectors) vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    /*
        Step-by-step:
            camera_center → the position of the camera in 3D space (like the eye of the viewer).
            - vec3(0, 0, focal_length) → move forward along the negative z-axis by the focal length.
                    -> This places the image plane (viewport) in front of the camera.
            - viewport_u / 2 → move half the width to the left (since viewport_u is the vector pointing horizontally across the viewport).
            - viewport_v / 2 → move half the height down (since viewport_v points downward or upward depending on your setup).
            So now, we’ve reached the upper-left corner of the rectangular viewport in world space.
    */
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;

    /*
        We don’t want the ray to go through the corner of the pixel — we want it to pass through the center of the pixel (for more accurate color sampling).
        pixel_delta_u = the horizontal distance between centers of two neighboring pixels.
        pixel_delta_v = the vertical distance between centers of two neighboring pixels.
        By adding:
        0.5 * (pixel_delta_u + pixel_delta_v)
        We move half a pixel right and half a pixel down, landing exactly in the center of the first pixel (pixel at row 0, column 0).
    */
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    /*
        Prints progress info (how many scanlines are left).
        Uses \r to overwrite the same line in the terminal.
        std::clog (instead of std::cout) means it wr ites to the error stream, so it won’t mix with the actual image data being written to stdout
    */

    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}