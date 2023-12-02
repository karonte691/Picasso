#pragma once

#ifndef PICASSO_ENGINE_H
#define PICASSO_ENGINE_H

#include <PEngine/PBuild.h>
#include <PEngine/Application.h>


namespace Picasso
{
    class PEngine
    {
    public:
        PEngine();
        ~PEngine();
        
        virtual void Run(Picasso::Config::AppConfig* config);
    
    private:
        Picasso::Engine::Application* m_app;
    };
}

#endif