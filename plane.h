#ifndef _PLANE_H
#define _PLANE_H
#include "color.h"
#include "Vector3f.h"
#include "object.h"

class plane : public Object {
private:
	Vector3f normal, center;
	double width, length, shine;
	color Ka, Kd, Ks;

public:
	plane();
	plane(Vector3f, Vector3f, double, double, color, color, color, double);

	double getWidth() { return width; }
	double getLength() { return length; }

	virtual double getShine() { return shine; }
	virtual Vector3f getCenter() { return center; }
	virtual Vector3f getNormalAt() { return normal; }
	virtual color getKa() { return Ka; }
	virtual color getKd() { return Kd; }
	virtual color getKs() { return Ks; }
	virtual bool isPlane() { return true; }
	virtual Vector3f getNormalAt(Vector3f v) { return normal; }
	virtual double findIntersection(ray ray);

};


#endif
