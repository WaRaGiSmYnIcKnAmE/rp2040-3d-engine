#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.h"
#include "Matrix4.h"
#include "Mesh.h"
#include "pico/float.h"

class Object
{
public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    Mesh *mesh;
    bool visible;

    Object() : position(Vector3()), rotation(Vector3()), scale(1.0f, 1.0f, 1.0f), mesh(nullptr), visible(true) {}

    void setPosition(const Vector3 &pos) { position = pos; }
    void setRotation(const Vector3 &rot) { rotation = rot; }
    void setScale(const Vector3 &scl) { scale = scl; }
    void setVisible(bool isVisible) { visible = isVisible; }

    Matrix4 getTransformationMatrix() const;
    Matrix4 getViewMatrix(const Vector3 &cameraPosition, const Vector3 &target, const Vector3 &up);
    Matrix4 getProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);
};

#endif // OBJECT_H
