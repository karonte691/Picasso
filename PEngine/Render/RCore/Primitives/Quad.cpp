#include <PEngine/Render/RCore/Primitives/Quad.h>

namespace Picasso::Engine::Render::Core::Primitives
{
    Quad::Quad()
    {
        Vertex vertices[] = {
            {{-0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
            {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
            {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
            {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3};

        unsigned int numVertices = sizeof(vertices) / sizeof(vertices[0]);
        unsigned int numIndices = sizeof(indices) / sizeof(indices[0]);

        _Setup(vertices, numVertices, indices, numIndices);
    }
}