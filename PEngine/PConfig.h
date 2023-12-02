#pragma once

#ifndef PCONFIG_H
#define PCONFIG_H

namespace Picasso::Config
{
    struct AppConfig
    {
        int startPositionX;
        int startPositionY;
        int startWidth;
        int startHeight;
        const char* appName;
    };
}

#endif