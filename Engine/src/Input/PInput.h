#pragma once

#ifndef P_INPUT_H
#define P_INPUT_H

#include "InputState.h"
#include "../Logger.h"

namespace Picasso::Engine::Input
{
    class PInput
    {
        public:
            void Init();
            void Update(double deltaTime);
            void Shutdown();
        private:
            pInputState m_inputState;
    };
}

#endif