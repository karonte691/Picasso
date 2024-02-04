#include <PEngine/Math/PMath.h>
#include <PEngine/Math/Constants.h>

namespace Picasso::Engine::Math
{
    float PMath::Deg2Rad(float degrees)
    {
        return degrees * P_DEG2RAD_MULTIPLIER;
    }

    float PMath::Rad2Deg(float radians)
    {
        return radians * P_RAD2DEG_MULTIPLIER;
    }
}