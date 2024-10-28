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

Matrix4 Object::getViewMatrix(const Vector3 &cameraPosition, const Vector3 &target, const Vector3 &up)
{
    Vector3 zAxis = normalizeVector(cameraPosition - target);
    Vector3 xAxis = normalizeVector(crossVectors(up, zAxis));
    Vector3 yAxis = crossVectors(zAxis, xAxis);

    Matrix4 viewMatrix;
    // Заполняем элементы матрицы построчно
    viewMatrix.data[0][0] = xAxis.x;
    viewMatrix.data[0][1] = yAxis.x;
    viewMatrix.data[0][2] = zAxis.x;
    viewMatrix.data[0][3] = float2fix(0.0f, FIXED_POINT_SHIFT);

    viewMatrix.data[1][0] = xAxis.y;
    viewMatrix.data[1][1] = yAxis.y;
    viewMatrix.data[1][2] = zAxis.y;
    viewMatrix.data[1][3] = float2fix(0.0f, FIXED_POINT_SHIFT);

    viewMatrix.data[2][0] = xAxis.z;
    viewMatrix.data[2][1] = yAxis.z;
    viewMatrix.data[2][2] = zAxis.z;
    viewMatrix.data[2][3] = float2fix(1.0f, FIXED_POINT_SHIFT);

    viewMatrix.data[3][0] = -xAxis.dot(cameraPosition);
    viewMatrix.data[3][1] = -yAxis.dot(cameraPosition);
    viewMatrix.data[3][2] = -zAxis.dot(cameraPosition);
    viewMatrix.data[3][3] = float2fix(1.0f, FIXED_POINT_SHIFT);
    return viewMatrix;
}

Matrix4 Object::getProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    float tanHalfFOV = tan(fov / 2.0f);
    float zRange = nearPlane - farPlane;

    Matrix4 projectionMatrix;
    // Заполняем элементы матрицы построчно
    projectionMatrix.data[0][0] = float2fix(1.0f / (tanHalfFOV * aspectRatio), FIXED_POINT_SHIFT);
    projectionMatrix.data[0][1] = 0;
    projectionMatrix.data[0][2] = 0;
    projectionMatrix.data[0][3] = 0;

    projectionMatrix.data[1][0] = 0;
    projectionMatrix.data[1][1] = float2fix(1.0f / tanHalfFOV, FIXED_POINT_SHIFT);
    projectionMatrix.data[1][2] = 0;
    projectionMatrix.data[1][3] = 0;

    projectionMatrix.data[2][0] = 0;
    projectionMatrix.data[2][1] = 0;
    projectionMatrix.data[2][2] = float2fix(-nearPlane - farPlane / zRange, FIXED_POINT_SHIFT);
    projectionMatrix.data[2][3] = float2fix(1.0f, FIXED_POINT_SHIFT);

    projectionMatrix.data[3][0] = 0;
    projectionMatrix.data[3][1] = 0;
    projectionMatrix.data[3][2] = (2 * farPlane * nearPlane) / zRange;
    projectionMatrix.data[3][3] = 0;

    return projectionMatrix;
}