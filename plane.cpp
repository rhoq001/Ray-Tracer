#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    vec3 temp = x1 - ray.endpoint;
    double x = dot(temp, normal);
    double temp2 = dot(ray.direction, normal);
    if(temp2 > -1e-6 || temp2 < 1e-6){
	x = x/temp2;
	if(x > 0){
	  Hit hit1;
	  hit1.t = x;
	  hit1.object = this;
	  hit1.ray_exiting = false;
	  hits.push_back(hit1);
	  return true;
	}
	return false;	
    }
    return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
