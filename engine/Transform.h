#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Matrix4.h"
#include "Vector3.h"

class Transform
{
public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Transform();
    Matrix4 getTransformationMatrix() const;
};

#endif // TRANSFORM_H
