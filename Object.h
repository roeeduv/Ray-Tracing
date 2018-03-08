#ifndef _OBJECT_H
#define _OBJECT_H
#include "color.h"
#include "Vector3f.h"
#include "ray.h"

class Object {

public:
	Object();
	virtual double findIntersection(ray r);
	virtual color getKa(); 
	virtual color getKd(); 
	virtual color getKs(); 
	virtual Vector3f getCenter();
	virtual Vector3f getNormalAt(Vector3f v); 
	virtual bool isPlane(); 
	virtual double getShine(); 
};

#endif