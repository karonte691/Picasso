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
        Math::Vector3 position;
        Math::Vector3 color;
        Math::Vector2 texcoord;
        Math::Vector3 normal;

        Vertex() : position(Math::Vector3()), color(Math::Vector3()), texcoord(Math::Vector2()), normal(Math::Vector3()) {}

        Vertex(const Math::Vector3 &pos, const Math::Vector3 &col, const Math::Vector2 &tex, const Math::Vector3 &norm)
            : position(pos), color(col), texcoord(tex), normal(norm) {}
    };
}

#endif