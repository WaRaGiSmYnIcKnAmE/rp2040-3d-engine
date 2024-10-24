#include "Render.h"
#include "../ILI9341.h"

void Render::renderSceneToBuffer(Scene scene, uint16_t* frameBuffer)
{
    // < Установка элементов сцены в буфер тут

    ili9341_init();

    ili9341_send_framebuffer(frameBuffer);
}

Vector3 projectVertex(Vector3& vertex, Camera& camera)
{
    return Vector3();
}

void renderTiangle(const Vertex& ver0, const Vertex& ver1, const Vertex& ver2, uint16_t framebuffer)
{

}

void renderMesh(const Mesh& mesh, uint16_t framebuffer)
{

}
