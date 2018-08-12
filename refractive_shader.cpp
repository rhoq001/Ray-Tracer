#include "refractive_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Refractive_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point,
        const vec3& same_side_normal, int recursion_depth,bool is_exiting) const
{
    //Hints: Use REFRACTIVE_INDICES::AIR for air refractive_index
    //       Use is_exiting to decide the refractive indices on the ray and transmission sides
    double air_refractive = 1;
    vec3 normal = same_side_normal.normalized();
    if(is_exiting) { normal *= -1.0; }
    vec3 reflection_color;
    vec3 refraction_color;
    double reflectance_ratio=-1;
    if(!world.disable_fresnel_refraction)
    {
        //TODO (Test 27+): Compute the refraction_color:
        double nr, ni;
	if(is_exiting){
	  ni = refractive_index;
	  nr = air_refractive;
	}
	else{
	  nr = refractive_index;
	  ni = air_refractive;
	}
	double cos_theta_i = dot(-1.0*ray.direction, normal);
	double total_internal = (1 - pow(ni/nr, 2)*(1 - pow(cos_theta_i, 2)));
	double cos_theta_r = sqrt(total_internal);
        // - Check if it is total internal reflection. 
        //      If so update the reflectance_ratio for total internal refraction
        if(total_internal < 0){
	   reflectance_ratio = 1;
	   refraction_color[0] = 0;
	   refraction_color[1] = 0;
	   refraction_color[2] = 0;
	}
        //      else, follow the instructions below
        else{
	   vec3 d = ray.direction;
	   vec3 T = (ni/nr)*(d - (dot(normal, d))*normal) - cos_theta_r*normal;
	   Ray ray_T(intersection_point, T.normalized());
	   recursion_depth++;
	   refraction_color = world.Cast_Ray(ray_T, recursion_depth);
	
        //        (Test 28+): Update the reflectance_ratio 
        //
        //        (Test 27+): Cast the refraction ray and compute the refraction_color
        //
           double R1 = pow(((nr*cos_theta_i - ni*cos_theta_r)/(nr*cos_theta_i + ni*cos_theta_r)), 2);
	   double R2 = pow(((ni*cos_theta_i - nr*cos_theta_r)/(ni*cos_theta_i + nr*cos_theta_r)), 2);
	   reflectance_ratio = (R1 + R2)/2;
	}
    }

    if(!world.disable_fresnel_reflection){
        //TODO:(Test 26+): Compute reflection_color:
        // - Cast Reflection Ray andd get color
        //
        vec3 r = ray.direction - 2.0*(dot(ray.direction, normal)*normal);
	Ray R;
	R.endpoint = intersection_point;
	R.direction = r;
	recursion_depth++;
	reflection_color = world.Cast_Ray(R, recursion_depth);
    }

    Enforce_Refractance_Ratio(reflectance_ratio);
    vec3 color;
    // TODO: (Test 26+) Compute final 'color' by blending reflection_color and refraction_color using 
    //                  reflectance_ratio
    color = (reflectance_ratio*reflection_color + (1 - reflectance_ratio)*refraction_color);
    return color;
}

void Refractive_Shader::
Enforce_Refractance_Ratio(double& reflectance_ratio) const
{
    if(world.disable_fresnel_reflection) reflectance_ratio=0;
    else if(world.disable_fresnel_refraction) reflectance_ratio=1;
}

