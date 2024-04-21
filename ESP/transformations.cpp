#include "transformations.hpp"
#include "memory.hpp"
#include "offsets.hpp"
#include "vector3.hpp"
#include <windows.h>

vector3_t transform_coordinate(const vector3_t& coord, const matrix_t& matrix) {
    vector3_t transformed_coord;

    // Perform matrix multiplication to transform coord
    transformed_coord.x = coord.x * matrix.m[0] + coord.y * matrix.m[1] + coord.z * matrix.m[2] + matrix.m[3];
    transformed_coord.y = coord.x * matrix.m[4] + coord.y * matrix.m[5] + coord.z * matrix.m[6] + matrix.m[7];
    transformed_coord.z = coord.x * matrix.m[8] + coord.y * matrix.m[9] + coord.z * matrix.m[10] + matrix.m[11];

    return transformed_coord;
}

bool world_to_screen(HANDLE processHandle, uintptr_t gameBaseAddress, const vector3_t& world_coord, vector2_t& screen_coord, HWND hwnd) {
    vector3_t invertedViewRight = memory::read_memory<vector3_t>(processHandle, gameBaseAddress + offsets::camera::inverted_view_right);
    vector3_t invertedViewUp = memory::read_memory<vector3_t>(processHandle, gameBaseAddress + offsets::camera::inverted_view_up);
    vector3_t invertedViewForward = memory::read_memory<vector3_t>(processHandle, gameBaseAddress + offsets::camera::inverted_view_forward);
    vector3_t invertedViewTranslation = memory::read_memory<vector3_t>(processHandle, gameBaseAddress + offsets::camera::inverted_view_translation);

    vector3_t viewPortSize = memory::read_memory<vector3_t>(processHandle, gameBaseAddress + offsets::camera::viewportsize);
    float projectionD1 = memory::read_memory<float>(processHandle, gameBaseAddress + offsets::camera::get_projection_d1);
    float projectionD2 = memory::read_memory<float>(processHandle, gameBaseAddress + offsets::camera::get_projection_d2);

    vector3_t temp = world_coord - invertedViewTranslation;
    float x = temp.dot(invertedViewRight);
    float y = temp.dot(invertedViewUp);
    float z = temp.dot(invertedViewForward);

    if (z < 0.65f) {
        return false;
    }

    screen_coord.x = viewPortSize.x * (1 + (x / projectionD1 / z));
    screen_coord.y = viewPortSize.y * (1 - (y / projectionD2 / z));

    return true;
}