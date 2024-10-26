#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.h"
#include "Matrix4.h"
#include "Mesh.h"

class Object
{
public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    Mesh *mesh;
    bool visible;

    Object() : position(Vector3()), rotation(Vector3()), scale(TO_FIXED(1), TO_FIXED(1), TO_FIXED(1)), mesh(nullptr), visible(true) {}

    void setPosition(const Vector3 &pos) { position = pos; }
    void setRotation(const Vector3 &rot) { rotation = rot; }
    void setScale(const Vector3 &scl) { scale = scl; }
    void setVisible(bool isVisible) { visible = isVisible; }

    Matrix4 getTransformationMatrix() const;
};

#endif // OBJECT_H
