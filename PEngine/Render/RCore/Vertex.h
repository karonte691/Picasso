#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <PEngine/Math/Vector2.h>
#include <PEngine/Math/Vector3.h>
#include <memory>

namespace Picasso::Engine::Render::Core
{
    struct Vertex
    {
        std::unique_ptr<Math::Vector3> position;
        std::unique_ptr<Math::Vector3> color;
        std::unique_ptr<Math::Vector2> texcoord;
    };
}

#endif