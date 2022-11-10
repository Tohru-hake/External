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
#include "RecoilCrosshair.hpp"
#include "AutoPistol.hpp"




namespace Overlay
{
    extern int iTab;

    extern bool bBoxes;
    extern bool bHealthbar;
    extern bool bRecoilCrosshair;
    

    extern bool bMenuVisible;
    HWND FindTopWindow(DWORD pid);
    int init(HINSTANCE instance, INT cmd_show);
}
