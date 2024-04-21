#include "memory.hpp"
#include "offsets.hpp"
#include "GameData.hpp" // Make sure to create this header file

std::vector<vector3_t> get_all_entities(HANDLE processHandle, uintptr_t gameBaseAddress) {
    std::vector<vector3_t> entities;
    // Example: Read the number of entities from a table size offset
    size_t entityCount = memory::read_memory<size_t>(processHandle, gameBaseAddress + offsets::world::near_entity_table_size);
    uintptr_t entityListBase = memory::read_memory<uintptr_t>(processHandle, gameBaseAddress + offsets::world::near_entity_table);

    for (size_t i = 0; i < entityCount; i++) {
        uintptr_t entityAddress = memory::read_memory<uintptr_t>(processHandle, entityListBase + i * sizeof(uintptr_t));
        vector3_t entityPosition = memory::read_memory<vector3_t>(processHandle, entityAddress + offsets::visual_state::position);
        entities.push_back(entityPosition);
    }

    return entities;
}