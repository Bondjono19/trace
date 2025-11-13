#include "ray.h"
#include "material.h"
#include "light.h"

// Apply the phong model to this point on the surface of the object, returning
// the color of that point.
vec3f Material::shade( Scene *scene, const ray& r, const isect& i ) const
{
	// YOUR CODE HERE

	// For now, this method just returns the diffuse color of the object.
	// This gives a single matte color for every distinct surface in the
	// scene, and that's it.  Simple, but enough to get you started.
	// (It's also inconsistent with the phong model...)

	// Your mission is to fill in this method with the rest of the phong
	// shading model, including the contributions of all the light sources.
    // You will need to call both distanceAttenuation() and shadowAttenuation()
    // somewhere in your code in order to compute shadows and light falloff.
	//return kd;
	Material material = i.getMaterial();
	vec3f position = r.at(i.t);
	vec3f normal = i.N;
	vec3f I = material.ke + material.ka * scene->getSettings()->getAmbientLight();
	std::cout << "amb light: " << scene->getSettings()->getAmbientLight() << std::endl;
	
	for (list<Light*>::const_iterator ite = scene->beginLights(); ite != scene->endLights(); ++ite) {
		Light* light = *ite;
		vec3f attenuation = light->distanceAttenuation(position)*light->shadowAttenuation(position);
		vec3f L = light->getDirection(position).normalize();
		vec3f N = normal.normalize();
		vec3f R = (2 * L.dot(N) * N - L).normalize();
		vec3f V = -r.getDirection().normalize();
		vec3f diffuse = prod(material.kd,light->getColor(position)) * max(0.0, L.dot(N));
		vec3f spec = prod(material.ks,light->getColor(position)) * pow(max(0.0, R.dot(V)), material.shininess);
		I += prod(attenuation,(diffuse + spec));
	}

	return I;
}
