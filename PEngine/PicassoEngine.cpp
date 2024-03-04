
#include <PEngine/PicassoEngine.h>

#include <stdio.h>
#include <iostream>

namespace Picasso
{
    /**
     * @brief Creates an instance of the PEngine class.
     *
     * @return A pointer to the created PEngine object.
     */
    extern "C" PEngine *create_object()
    {
        return new PEngine();
    }

    /**
     * @brief Destroys an instance of the PEngine class.
     *
     * @param obj A pointer to the PEngine object to be destroyed.
     */
    extern "C" void destroy_object(PEngine *obj)
    {
        delete obj;
    }

    /**
     * @brief Constructs a PEngine object.
     *
     * This constructor initializes the m_app member variable with a new instance of the Picasso::Engine::Application class.
     */
    PEngine::PEngine()
    {
        m_app = new Picasso::Engine::Application();
    }

    /**
     * @brief Destructs a PEngine object.
     *
     * This destructor deletes the m_app member variable.
     */
    PEngine::~PEngine()
    {
        delete m_app;
    }

    /**
     * @brief Runs the Picasso Engine with the specified configuration.
     *
     * @param config A pointer to the Picasso::Config::AppConfig object containing the engine configuration.
     */
    void PEngine::Run(Picasso::Config::AppConfig *config)
    {
        if (!m_app->Create(config))
        {
            return;
        }

        m_app->Run();
    }
}