#ifndef _ray_H
#define _ray_H
#include "Vector3f.h"

class ray {
private:
	Vector3f origin, dir;
public:
	ray();
	ray(Vector3f, Vector3f);
	Vector3f getOrigin();
	Vector3f getDir();

};


#endif
