#ifndef RENDER_H
#define RENDER_H

#include "Vertex.h"
#include "Mesh.h"
#include "Matrix4.h"

struct Camera
{
    Vector3 position;
    Matrix4 projectionMatrix;

    Camera(Vector3 pos, Matrix4 projMatrix) : position(pos) , projectionMatrix(projMatrix) {};
};

struct Scene {
    Mesh* meshes;

    int meshCount;
    Camera camera;

    Scene() : meshCount(0), camera(Vector3(0, 0, 0), Matrix4().identity()) {};
    Scene(Mesh* meshes, int meshCount, Camera camera) : meshes(meshes), meshCount(meshCount), camera(camera) {};
};

class Render {
    public:
        void renderSceneToBuffer(Scene scene, uint16_t* frameBuffer);
    private:
        Vector3 projectVertex(Vector3& vertex, Camera& camera);
        void renderTiangle(const Vertex& ver0, const Vertex& ver1, const Vertex& ver2, uint16_t framebuffer);
        void renderMesh(const Mesh& mesh, uint16_t framebuffer);
};

#endif //RENDER_H