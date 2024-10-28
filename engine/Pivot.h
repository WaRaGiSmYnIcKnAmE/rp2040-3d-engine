#ifndef PIVOT_H
#define PIVOT_H

#include "Vector3.h"
#include "Matrix4.h"

class Pivot
{
public:
    Vector3 position = Vector3();
    Vector3 rotation = Vector3();

    Pivot() : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f) {};
    Pivot(Vector3 &positionObj, Vector3 &rotationObj) : position(positionObj), rotation(rotationObj) {};

    Matrix4 objectMatrix() const;
};

#endif