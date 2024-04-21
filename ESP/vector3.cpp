#include "memory.hpp" 
#include "vector3.hpp" 
#include "offsets.hpp" 

// Function to read an entity's position
vector3_t get_entity_position(HANDLE process, uintptr_t entityBase) {
    uintptr_t positionAddress = entityBase + offsets::visual_state::position;
    float x = memory::read_memory<float>(process, positionAddress);
    float y = memory::read_memory<float>(process, positionAddress + sizeof(float));
    float z = memory::read_memory<float>(process, positionAddress + 2 * sizeof(float));
    return vector3_t(x, y, z);
}