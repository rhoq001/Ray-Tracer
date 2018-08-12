#include "boolean.h"


// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    if(type == type_union){
	bool uni = false;
	if(A->Intersection(ray, hits)){
	   uni = true;
	}
	if(B->Intersection(ray, hits)){
	   uni = true;
	}
	return uni;		
    }
    return false;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(true);
    return vec3();
}
