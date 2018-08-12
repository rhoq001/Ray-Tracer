#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const
{
    vec3 normal = same_side_normal.normalized();
    if(is_exiting) { normal *= -1.0;}
    vec3 color;
    vec3 r = ray.direction - 2.0*(dot(ray.direction, normal)*normal);
    Ray R;
    R.endpoint = intersection_point;
    R.direction = r;
    recursion_depth++;
    vec3 reflected_color = world.Cast_Ray(R, recursion_depth);
    vec3 shader_color = shader->Shade_Surface(ray, intersection_point, same_side_normal, recursion_depth, is_exiting);
    color = (reflectivity*reflected_color + (1 - reflectivity) * shader_color); 
    // TODO: determine the color
    return color;
}
