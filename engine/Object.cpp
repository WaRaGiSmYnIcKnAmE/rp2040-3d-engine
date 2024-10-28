#include "Object.h"

// Получение итоговой матрицы трансформации для объекта
Matrix4 Object::getTransformationMatrix() const
{
    Matrix4 translationMatrix = Matrix4::translation(position.x, position.y, position.z);
    Matrix4 rotationMatrix = Matrix4::rotationX(TO_FIXED(rotation.x)) *
                             Matrix4::rotationY(TO_FIXED(rotation.y)) *
                             Matrix4::rotationZ(TO_FIXED(rotation.z));
    Matrix4 scaleMatrix = Matrix4::scale(scale.x, scale.y, scale.z);

    return translationMatrix.multiply(rotationMatrix).multiply(scaleMatrix);
}