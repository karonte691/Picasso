#pragma once

#ifndef PICASSO_CONTROLLER_H
#define PICASSO_CONTROLLER_H

#include <string>

namespace Picasso::Engine::Controller
{
    class PicassoController
    {
    public:
        PicassoController() = default;
        PicassoController(const std::string &name = "") : m_ControllerName(name){};
        virtual ~PicassoController(){};

        virtual bool InitController() = 0;
        virtual void Update() = 0;

        inline const std::string GeControllerName() const { return m_ControllerName; }

    protected:
        std::string m_ControllerName;
    };
}

#endif // PICASSO_CONTROLLER_H