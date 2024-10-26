#include "Camera.h"

// Установка позиции
void Camera::setPosition(int x, int y, int z)
{
    position = Vector3(x, y, z);
}

// Установка поворота
void Camera::setRotation(int xAngle, int yAngle, int zAngle)
{
    rotation = Vector3(xAngle, yAngle, zAngle);
}

// Перемещение вперед
void Camera::moveForward(int distance)
{
    position.z += distance; // Перемещение по оси Z
}

// Перемещение вправо
void Camera::moveRight(int distance)
{
    position.x += distance; // Перемещение по оси X
}

// Перемещение вверх
void Camera::moveUp(int distance)
{
    position.y += distance; // Перемещение по оси Y
}

// Получение View Matrix для камеры (инверсия положения и поворота)
Matrix4 Camera::getViewMatrix() const
{
    Matrix4 translationMatrix = Matrix4::translation(-position.x, -position.y, -position.z);
    Matrix4 rotationXMatrix = Matrix4::rotationX(-rotation.x);
    Matrix4 rotationYMatrix = Matrix4::rotationY(-rotation.y);
    Matrix4 rotationZMatrix = Matrix4::rotationZ(-rotation.z);

    return rotationZMatrix * rotationYMatrix * rotationXMatrix * translationMatrix;
}
