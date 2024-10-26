#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include "Camera.h"

#define MAX_OBJECTS 100

class Scene
{
public:
    Object *objects[MAX_OBJECTS];
    int objectCount;

    Scene() : objectCount(0) {}

    // Добавление объекта в сцену
    bool addObject(Object *obj)
    {
        if (objectCount >= MAX_OBJECTS)
            return false;
        objects[objectCount++] = obj;
        return true;
    }

    // Удаление объекта из сцены
    bool removeObject(Object *obj)
    {
        for (int i = 0; i < objectCount; ++i)
        {
            if (objects[i] == obj)
            {
                objects[i] = objects[--objectCount];
                return true;
            }
        }
        return false;
    }

    // Фильтр объектов на основе видимости камеры
    void filterVisibleObjects(Camera &camera)
    {
        for (int i = 0; i < objectCount; ++i)
        {
            if (!camera.isInView(objects[i]->position))
            {
                // Исключить объект из рендера, если он вне поля зрения
                objects[i]->setVisible(false);
            }
            else
            {
                objects[i]->setVisible(true);
            }
        }
    }
};

#endif // SCENE_H