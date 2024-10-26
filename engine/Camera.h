#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix4.h"

class Camera
{
public:
    Vector3 position;
    Vector3 rotation;

    int fieldOfView; // Угол обзора
    int nearPlane;   // Ближняя плоскость отсечения
    int farPlane;    // Дальняя плоскость отсечения

    Camera() : position(Vector3(TO_FIXED(0), TO_FIXED(0), TO_FIXED(0))), rotation(Vector3(TO_FIXED(0), TO_FIXED(0), TO_FIXED(0))), fieldOfView(TO_FIXED(90)), nearPlane(TO_FIXED(1)), farPlane(TO_FIXED(1000)) {}

    // Установка позиции и поворота камеры
    void setPosition(const Vector3 &pos)
    {
        position = pos;
    }
    void setRotation(const Vector3 &rot)
    {
        rotation = rot;
    }

    // Проверка видимости точки относительно камеры
    bool isInView(const Vector3 &point)
    {
        // Преобразовать точку в пространство камеры, используя матрицы трансформации
        Vector3 viewPos = transformToViewSpace(point);

        // Проверка по полю зрения и плоскостям отсечения
        return (viewPos.z >= nearPlane && viewPos.z <= farPlane);
    }

    // Методы для изменения положения
    void setPosition(int x, int y, int z);
    void setRotation(int xAngle, int yAngle, int zAngle);

    // Методы для передвижения
    void moveForward(int distance);
    void moveRight(int distance);
    void moveUp(int distance);

    // Получение матрицы вида (View Matrix)
    Matrix4 getViewMatrix() const;

private:
    // Трансформация в пространство камеры
    Vector3 transformToViewSpace(const Vector3 &point)
    {
        Matrix4 rotationMatrix = Matrix4::rotationX(rotation.x) * Matrix4::rotationY(rotation.y) * Matrix4::rotationZ(rotation.z);
        Vector3 translatedPoint = point - position;
        return rotationMatrix.multiply(translatedPoint);
    }
};

#endif // CAMERA_H
