#pragma once

#ifndef PICASSO_ENGINE_H
#define PICASSO_ENGINE_H

#include "Common.h"
#include "PBuild.h"
#include "Application.h"

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