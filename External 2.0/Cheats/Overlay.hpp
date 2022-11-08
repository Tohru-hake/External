#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <d3d11.h>
#include <dwmapi.h>

#include "../Components/Entity.hpp"
#include "../Components/LocalPlayer.hpp"
#include "../Math/Math.hpp"
#include "Aimbot.hpp"
#include "Bhop.hpp"




namespace Overlay
{
    extern int test;
    extern bool bMenuVisible;
    int init(HINSTANCE instance, INT cmd_show);
}
