#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    vec3 p = ray.endpoint - center;
    vec3 u = ray.direction;
    double t1, t2;
    Hit hit1;
    Hit hit2;
    double discrim = 4*(pow(dot(u, p), 2) - (dot(p, p) - pow(radius, 2)));
    if(discrim >= 0){
	double b = 2*dot(u, p);
	//double c = dot(p, p) - pow(radius, 2);
	t1 = (-1*b - sqrt(discrim))/2;
	t2 = (-1*b + sqrt(discrim))/2;
	if(discrim < 1e-6){
	  t1 = 0; 
	}
	hit1.t = t1;
	hit1.object = this;
	hit1.ray_exiting = false;
	hits.push_back(hit1);

	hit2.t = t2;
	hit2.object = this;
	hit2.ray_exiting = true;
	hits.push_back(hit2);
	return true;
    }
    // TODO
    return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    normal = (point - center).normalized();
    // TODO: set the normal
    return normal;
}
