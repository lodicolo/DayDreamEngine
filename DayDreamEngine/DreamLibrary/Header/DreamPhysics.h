#pragma once
#include <DreamMath.h>



class DreamPhysics {
public:
	static bool Sphere_SphereCollision(DreamMath::DreamVector3 position1, float radius1, DreamMath::DreamVector3 position2, float radius2);
};
