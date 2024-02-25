#pragma once

#ifndef P_INPUT_H
#define P_INPUT_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/Input/InputState.h>
#include <PEngine/Input/InputListener.h>

#include <memory>

namespace Picasso::Engine::Input
{
    class PInput
    {
    public:
        void Init();
        void Shutdown();

    private:
        pInputState m_inputState;
        std::unique_ptr<InputListener> p_InputListener;
    };
}

#endif