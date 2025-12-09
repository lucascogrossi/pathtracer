#include "common.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"

int main() {
    hittable_list world;

    auto ground_material = make_shared<metal>(color(0.1, 0.1, 0.15), 0.3);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int i = 0; i < 12; i++) {
        double angle = i * 0.524;
        double radius = 2.0 + i * 0.3;
        double height = 0.3 + i * 0.15;
        
        point3 center(radius * cos(angle), height, radius * sin(angle));
        auto glass_mat = make_shared<dielectric>(1.5);
        world.add(make_shared<sphere>(center, 0.3 + i * 0.05, glass_mat));
    }

    for (int ring = 0; ring < 3; ring++) {
        double ring_radius = 5.0 + ring * 1.5;
        double ring_height = 2.0 + ring * 0.8;
        int spheres_in_ring = 8 + ring * 2;
        
        for (int i = 0; i < spheres_in_ring; i++) {
            double angle = (i * 2 * pi) / spheres_in_ring;
            point3 center(ring_radius * cos(angle), ring_height, ring_radius * sin(angle));
            
            auto metal_color = color(
                0.7 + ring * 0.1,
                0.3 + 0.2 * sin(angle),
                0.5 + 0.2 * cos(angle)
            );
            auto metal_mat = make_shared<metal>(metal_color, 0.1);
            world.add(make_shared<sphere>(center, 0.25, metal_mat));
        }
    }

    auto hero1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(-3, 1.2, -2), 1.2, hero1));
    
    auto hero2 = make_shared<lambertian>(color(0.9, 0.1, 0.3));
    world.add(make_shared<sphere>(point3(3, 1.2, -2), 1.2, hero2));
    
    auto hero3 = make_shared<metal>(color(0.9, 0.8, 0.2), 0.0);
    world.add(make_shared<sphere>(point3(0, 1.8, 2), 1.2, hero3));

    for (int i = 0; i < 20; i++) {
        double angle = random_double(0, 2 * pi);
        double dist = random_double(7, 10);
        point3 center(dist * cos(angle), random_double(0.15, 0.4), dist * sin(angle));
        
        auto choose_mat = random_double();
        shared_ptr<material> sphere_material;
        
        if (choose_mat < 0.4) {
            auto albedo = color(random_double(0.7, 1), random_double(0.3, 0.8), random_double(0.3, 0.8));
            sphere_material = make_shared<lambertian>(albedo);
        } else if (choose_mat < 0.7) {
            auto albedo = color(random_double(0.6, 1), random_double(0.6, 1), random_double(0.6, 1));
            sphere_material = make_shared<metal>(albedo, random_double(0, 0.3));
        } else {
            sphere_material = make_shared<dielectric>(1.5);
        }
        
        world.add(make_shared<sphere>(center, random_double(0.15, 0.35), sphere_material));
    }

    camera cam;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 500;
    cam.max_depth         = 50;
    
    cam.vfov     = 35;
    cam.lookfrom = point3(8, 4, 10);
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0);
    
    cam.defocus_angle = 0.3;
    cam.focus_dist    = 11.0;
    
    cam.render(world);
}