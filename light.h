#ifndef _LIGHT_H
#define _LIGHT_H
#include "Vector3f.h"
#include "color.h"

class light {
	Vector3f direction, position;
	color intensity;
	float cutoff;

public:
	light();
	light(Vector3f, color);
	light(Vector3f, color, Vector3f, float);

	Vector3f getPosition() { return position; }
	Vector3f getDirection() { return direction; }
	color getIntensity() { return intensity; }
	float getCutOff() { return cutoff; }

};
light::light() {
	position = Vector3f(1, 0, 0);
	direction = Vector3f(1, 0, 0);
	intensity = color(1, 1, 1);
	cutoff = 360;
}

light::light(Vector3f d, color c) {
	direction = d;
	intensity = c;
	position = Vector3f(1, 0, 0);
	cutoff = 360;
}

light::light(Vector3f d, color c, Vector3f p, float cut)
{
	direction = d;
	intensity = c;
	position = p;
	cutoff = cut;
}
#endif