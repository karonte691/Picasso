#pragma once

#ifndef PICASSO_ENGINE_H
#define PICASSO_ENGINE_H

#include <PEngine/PBuild.h>
#include <PEngine/Core/Application.h>

namespace Picasso
{
    class PEngine
    {
    public:
        PEngine();
        ~PEngine();

        void Run(Picasso::Config::AppConfig *config);

    private:
        Picasso::Engine::Core::Application *m_app;
    };
}

#endif