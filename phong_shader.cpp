#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const  vec3& same_side_normal,int recursion_depth,bool is_exiting) const 
{
    vec3 color;
    // TODO: determine the color
    color = color_ambient*world.ambient_color*world.ambient_intensity;
    vec3 normal = same_side_normal.normalized();
    if(is_exiting) {normal = -1.0*normal;};
    
    for(unsigned i = 0; i < (world.lights).size(); i++){
	vec3 lightSource = ((world.lights[i]->position) - intersection_point);
	vec3 l = lightSource.normalized();
	vec3 r = (2.0*dot(l, normal)*normal)-l;
	vec3 temp = ((color_diffuse*world.lights[i]->Emitted_Light(ray)*std::max(dot(l, normal), 0.0)) + (color_specular*world.lights[i]->Emitted_Light(ray)*pow(std::max(dot(r.normalized(), (ray.endpoint - intersection_point).normalized()), 0.0), specular_power)))/lightSource.magnitude_squared();
	if(world.enable_shadows){
	   Ray shadow_ray;
	   shadow_ray.endpoint = intersection_point;
	   shadow_ray.direction = l;
	   Hit h1;
	   Object* obj = world.Closest_Intersection(shadow_ray, h1);
	   if(obj){
		double x1 = lightSource.magnitude();
		double x2 = h1.t;
		if(x1 < x2){
		   color = color + temp;
		}
	   }
	   else{
		color = color + temp;
	   }
	}
	else{
	   color = color + temp;
	}
    }
    
    
    return color;
}

