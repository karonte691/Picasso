#include <PEngine/EventSystem/PERegistry.h>

namespace Picasso::Engine::EventSystem
{
    // private, defined in PERegistry.h
    std::unordered_map<std::string, std::vector<std::size_t>> PicassoRegistry::m_slotIdsMap;
}
