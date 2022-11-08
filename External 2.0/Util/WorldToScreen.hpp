#pragma once

//Use this to transform an entities 3D position in-game to a 2D position on your screen for example - to render something on them (Wallhacks)

struct ViewMatrix {
    ViewMatrix() noexcept
        : data() {}

    float* operator[](int index) noexcept {
        return data[index];
    }

    const float* operator[](int index) const noexcept {
        return data[index];
    }

    float data[4][4];
};

static bool WorldToScreen(const Vector3& world, Vector3& screen, const ViewMatrix& vm) noexcept {
    float w = vm[3][0] * world.x + vm[3][1] * world.y + vm[3][2] * world.z + vm[3][3];

    if (w < 0.001f) {
        return false;
    }

    const float x = world.x * vm[0][0] + world.y * vm[0][1] + world.z * vm[0][2] + vm[0][3];
    const float y = world.x * vm[1][0] + world.y * vm[1][1] + world.z * vm[1][2] + vm[1][3];

    w = 1.f / w;
    float nx = x * w;
    float ny = y * w;

    //const ImVec2 size = ImGui::GetIO().DisplaySize;

    auto SizeX = GetSystemMetrics(SM_CXSCREEN);
    auto SizeY = GetSystemMetrics(SM_CYSCREEN);
    screen.x = (SizeX * 0.5f * nx) + (nx + SizeX * 0.5f);
    screen.y = -(SizeY * 0.5f * ny) + (ny + SizeY * 0.5f);

    return true;
}