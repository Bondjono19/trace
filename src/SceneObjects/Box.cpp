#include <cmath>
#include <assert.h>

#include "Box.h"

bool Box::intersectLocal( const ray& r, isect& i ) const
{
	// YOUR CODE HERE:
    // Add box intersection code here.
	// it currently ignores all boxes and just returns false.

	// slab method

	vec3f o = r.getPosition();	
	vec3f d = r.getDirection();
	double t1x = (-0.5 - o[0]) / d[0];
	double t2x = (0.5 - o[0]) / d[0];
	double t1y = (-0.5 - o[1]) / d[1];
	double t2y = (0.5 - o[1]) / d[1];
	double t1z = (-0.5 - o[2]) / d[2];
	double t2z = (0.5 - o[2]) / d[2];


	double txclose = std::min({t1x, t2x});
	double tyclose = std::min({t1y, t2y});
	double tzclose = std::min({t1z, t2z});
	double txfar = std::max({t1x, t2x});
	double tyfar = std::max({t1y, t2y});
	double tzfar = std::max({t1z, t2z});

	double tclose = std::max({txclose, tyclose, tzclose});
	double tfar = std::min({txfar, tyfar, tzfar});

	if (tclose < tfar && tfar > 0) {
		double thit;
		vec3f normal;
		if (tclose > 0) {
			thit = tclose;

			if (tclose == txclose) {
				normal = (t1x < t2x) ? vec3f(-1, 0, 0) : vec3f(1, 0, 0);
			} else if (tclose == tyclose) {
				normal = (t1y < t2y) ? vec3f(0, -1, 0) : vec3f(0, 1, 0);
			} else {
				normal = (t1z < t2z) ? vec3f(0, 0, -1) : vec3f(0, 0, 1);
			}
		} else {
			thit = tfar;

			if (tfar == txfar) {
				normal = (t1x > t2x) ? vec3f(-1, 0, 0) : vec3f(1, 0, 0);
			} else if (tfar == tyfar) {
				normal = (t1y > t2y) ? vec3f(0, -1, 0) : vec3f(0, 1, 0);
			} else {
				normal = (t1z > t2z) ? vec3f(0, 0, -1) : vec3f(0, 0, 1);
			}
		}
		i.setT(thit);
		i.setN(normal);
		i.obj = this;
		return true;
	}
	else {
		return false;
	}
}
