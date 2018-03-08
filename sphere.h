#ifndef _SPHERE_H
#define _SPHERE_H
#include "color.h"
#include "Vector3f.h"
#include "object.h"

class sphere : public Object {
	Vector3f center;
	double radius, shine;
	color Ka, Kd, Ks;

public:
	sphere();
	sphere(Vector3f, double, color, color, color, double);

	double getRadius() { return radius; }
	virtual double getShine() { return shine; }
	virtual Vector3f getCenter() { return center; }
	virtual color getKa() { return Ka; }
	virtual color getKd() { return Kd; }
	virtual color getKs() { return Ks; }
	virtual bool isPlane() { return false; }
	virtual double findIntersection(ray ray); 
	virtual  Vector3f getNormalAt(Vector3f v);
	
};


#endif