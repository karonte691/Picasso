#include "PicassoEngine.h"
#include <stdio.h>
#include <iostream>


namespace Picasso
{
    extern "C" PEngine* create_object()
    {
        return new PEngine();
    }

    extern "C" void destroy_object(PEngine* obj)
    {
        delete obj;
    }

    PEngine::PEngine()
    {
        m_app = new Picasso::Engine::Application();
    }

    PEngine::~PEngine()
    {
        delete m_app;
    }

    void PEngine::Run(Picasso::Config::AppConfig* config)
    {
       m_app->Create(config);
       
       m_app->Run();
    }
}