/**
 * @file hittable_list.h
 * @brief Defines the `hittable_list` class that stores and manages multiple hittable objects.
 *
 * A `hittable_list` represents a collection of objects that can be intersected by rays.
 * It extends the `hittable` interface and checks for the nearest intersection among all contained objects.
 */

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>

/**
 * @class hittable_list
 * @brief A container class for storing multiple hittable objects.
 *
 * This class maintains a list of objects (like spheres or planes)
 * and determines whether a given ray hits any of them.
 * It keeps track of the closest intersection point to ensure correct rendering.
 */
class hittable_list : public hittable
{
public:
    std::vector<shared_ptr<hittable>> objects; ///< List of scene objects

    /**
     * @brief Default constructor.
     * Initializes an empty hittable list.
     */
    hittable_list() {}

    /**
     * @brief Constructs a hittable list containing one object.
     * @param object Pointer to the hittable object to add.
     */
    hittable_list(shared_ptr<hittable> object) { add(object); }

    /**
     * @brief Removes all objects from the list.
     */
    void clear() { objects.clear(); }

    /**
     * @brief Adds a new hittable object to the list.
     * @param object Shared pointer to the hittable object.
     */
    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    /**
     * @brief Checks for the nearest intersection of a ray with any object in the list.
     *
     * Iterates over all hittable objects and records the closest valid hit within the range `[ray_t.min, ray_t.max]`.
     *
     * @param r Incoming ray.
     * @param ray_t Range of valid ray distances.
     * @param rec Output record storing hit details (position, normal, material, etc.).
     * @return True if the ray intersects any object, false otherwise.
     */
    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        // Iterate through all objects to find the nearest intersection
        for (const auto &object : objects)
        {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif


