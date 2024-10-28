#include "Object.h"

// Получение итоговой матрицы трансформации для объекта
Matrix4 Object::getTransformationMatrix() const
{
    Matrix4 translationMatrix = Matrix4::translation(position.x, position.y, position.z);
    Matrix4 rotationMatrix = Matrix4::rotationX(rotation.x) *
                             Matrix4::rotationY(rotation.y) *
                             Matrix4::rotationZ(rotation.z);
    Matrix4 scaleMatrix = Matrix4::scale(scale.x, scale.y, scale.z);

    return translationMatrix * rotationMatrix * scaleMatrix;
}