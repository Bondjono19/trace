#include <cmath>

#include "light.h"

double DirectionalLight::distanceAttenuation( const vec3f& P ) const
{
	// distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


vec3f DirectionalLight::shadowAttenuation( const vec3f& P ) const
{
	vec3f dir = -this->orientation.normalize();
	isect i;
	ray ray(P, dir);
	bool hit = scene->intersect(ray,i);
	if (hit && i.t > 0) {
		return vec3f(0, 0, 0);
	}
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.
    return vec3f(1,1,1);
}

vec3f DirectionalLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f DirectionalLight::getDirection( const vec3f& P ) const
{
	return -orientation;
}

double PointLight::distanceAttenuation( const vec3f& P ) const
{
	// YOUR CODE HERE
	double distance = (this->position - P).length();

	// You'll need to modify this method to attenuate the intensity 
	// of the light based on the distance between the source and the 
	// point P.  For now, I assume no attenuation and just return 1.0

	float attenConst = scene->getSettings()->getAttenConst();
	float attenLinear = scene->getSettings()->getAttenLinear();
	float attenQuadric = scene->getSettings()->getAttenQuadric();
	return 1.0/(attenConst + attenLinear*distance + attenQuadric*distance*distance);
}

vec3f PointLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f PointLight::getDirection( const vec3f& P ) const
{
	return (position - P).normalize();
}


vec3f PointLight::shadowAttenuation(const vec3f& P) const
{
	vec3f dir = (this->position - P).normalize();
	isect i;
	ray ray(P, dir);
	bool hit = scene->intersect(ray,i);
	if (hit) {
		return vec3f(0, 0, 0);
	}
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.
    return vec3f(1,1,1);
}
