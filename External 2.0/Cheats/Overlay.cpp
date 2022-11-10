#include "Overlay.hpp"
#include "../Memory/Memory.hpp"

bool Overlay::bMenuVisible = false;
int Overlay::iTab = 0;

bool Overlay::bBoxes = false;
bool Overlay::bHealthbar = false;
bool Overlay::bRecoilCrosshair = false;
int RecoilCrosshair::opacity = 0;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
    if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param)) {
        return 1L;
    }

    switch (message) {
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0L;
    }
    }

    return DefWindowProc(window, message, w_param, l_param);
}

static void makeNormal(HWND hwnd)
{
    //Remove the WS_EX_TRANSPARENT flag from the extended window style
    int extendedStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    SetWindowLong(hwnd, GWL_EXSTYLE, extendedStyle & ~WS_EX_TRANSPARENT);
}

static void makeTransparent(HWND hwnd)
{
    // Change the extended window style to include WS_EX_TRANSPARENT
    int extendedStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    SetWindowLong(hwnd, GWL_EXSTYLE, extendedStyle | WS_EX_TRANSPARENT);
}

void ShowMenu(HWND Window)
{
    makeNormal(Window);
    SetFocus(Window);
    SetForegroundWindow(Window);
}

HWND Overlay::FindTopWindow(DWORD pid)
{
    std::pair<HWND, DWORD> params = { 0, pid };

    // Enumerate the windows using a lambda to process each window
    BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
        {
            auto pParams = (std::pair<HWND, DWORD>*)(lParam);

            DWORD processId;
            if (GetWindowThreadProcessId(hwnd, &processId) && processId == pParams->second)
            {
                // Stop enumerating
                SetLastError(-1);
                pParams->first = hwnd;
                return FALSE;
            }

            // Continue enumerating
            return TRUE;
        }, (LPARAM)&params);

    if (!bResult && GetLastError() == -1 && params.first)
    {
        return params.first;
    }

    return 0;
}

void Hidemenu(HWND Window)
{
    makeTransparent(Window);
    SetFocus(Overlay::FindTopWindow(pID));
    SetForegroundWindow(Overlay::FindTopWindow(pID));
}

template <class T>
inline void RenderBox(T x1, T y1, T x2, T y2, ImColor color, float thickness = 1.f, float rounding = 0.f) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), ImColor(color), rounding, 15, thickness);
}

int Overlay::init(HINSTANCE instance, INT cmd_show)
{
    // create our window class to specify options for our window
    const WNDCLASSEXW wc{
        .cbSize = sizeof(WNDCLASSEXW),
        .style = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = window_procedure,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = instance,
        .hIcon = nullptr,
        .hCursor = nullptr,
        .hbrBackground = nullptr,
        .lpszMenuName = nullptr,
        .lpszClassName = L"Hydra", // non-visible class name
        .hIconSm = nullptr
    };

    // register it and make sure it succeeded
    if (!RegisterClassExW(&wc)) {
        return FALSE;
    }

    // create our window
    const HWND window = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
        wc.lpszClassName,
        L"Hydra", //actual window name
        WS_POPUP,
        0,
        0,
        Width,
        Height,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr
    );

    // make sure the window was created successfully
    if (!window) {
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return FALSE;
    }

    // set the window's opacity
    if (!SetLayeredWindowAttributes(window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA)) {
        DestroyWindow(window);
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return FALSE;
    }

    {
        RECT client_area{};
        if (!GetClientRect(window, &client_area)) {
            DestroyWindow(window);
            UnregisterClassW(wc.lpszClassName, wc.hInstance);
            return FALSE;
        }

        RECT window_area{};
        if (!GetWindowRect(window, &window_area)) {
            DestroyWindow(window);
            UnregisterClassW(wc.lpszClassName, wc.hInstance);
            return FALSE;
        }

        POINT diff{};
        if (!ClientToScreen(window, &diff)) {
            DestroyWindow(window);
            UnregisterClassW(wc.lpszClassName, wc.hInstance);
            return FALSE;
        }

        const MARGINS margins{
            window_area.left + (diff.x - window_area.left),
            window_area.top + (diff.y - window_area.top),
            client_area.right,
            client_area.bottom
        };

        if (FAILED(DwmExtendFrameIntoClientArea(window, &margins))) {
            DestroyWindow(window);
            UnregisterClassW(wc.lpszClassName, wc.hInstance);
            return FALSE;
        }
    }

    // create our directx swap chain description
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));

    sd.BufferDesc.Width = 0U;
    sd.BufferDesc.Height = 0U;
    sd.BufferDesc.RefreshRate.Numerator = 60U;
    sd.BufferDesc.RefreshRate.Denominator = 1U;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    sd.SampleDesc.Count = 1U;
    sd.SampleDesc.Quality = 0U;

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2U;
    sd.OutputWindow = window;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    constexpr D3D_FEATURE_LEVEL feature_levels[2]{
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_0
    };


    D3D_FEATURE_LEVEL feature_level{};

    // directx variables
    ID3D11Device* device{ nullptr };
    ID3D11DeviceContext* device_context{ nullptr };
    IDXGISwapChain* swap_chain{ nullptr };
    ID3D11RenderTargetView* render_target_view{ nullptr };

    // create the swap chain & device
    if (FAILED(D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0U,
        feature_levels,
        2U,
        D3D11_SDK_VERSION,
        &sd,
        &swap_chain,
        &device,
        &feature_level,
        &device_context))) {
        DestroyWindow(window);
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return FALSE;
    }

    ID3D11Texture2D* back_buffer{ nullptr };

    if (FAILED(swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer)))) {
        return FALSE;
    }

    // create our render target
    if (FAILED(device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view))) {
        return FALSE;
    }

    if (back_buffer) {
        back_buffer->Release();
    }

    // tell windows to show this window
    ShowWindow(window, cmd_show);
    UpdateWindow(window);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(device, device_context);
    
    bool running = true;
    while (running) {
        
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT) {
                running = false;
            }
        }

        if (!running) {
            break;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        for (int i = 1; i < 32; i++)
        {
            const DWORD Base = Entity::getEntBase(i);

            if (!Base)
                continue;

            if (!(Entity::isAlive(Base) && Entity::getEntTeam(Base) != 0))
                continue;

            if (Entity::getEntTeam(Base) == LocalPlayer::getLocalTeam())
                continue;

            auto head = Entity::getEntBonePos(Base, 8);
            auto feet = Entity::getEntPos(Base);
            auto matrix = LocalPlayer::getLocalViewMatrix();
            Vector3 top;
            Vector3 bottom;
            
            if (WorldToScreen(head + Vector3{ 0, 0, 11.f }, top, matrix) && WorldToScreen(feet - Vector3{ 0, 0, 7.f }, bottom, matrix)) {
                const float h = bottom.y - top.y;
                const float w = h * 0.35f;

                if (Entity::isDormant(Base))
                {
                    if (Overlay::bBoxes)
                    {
                        ImGui::GetBackgroundDrawList()->AddRect({ top.x - w, top.y }, { top.x + w, bottom.y }, ImColor(100.f, 100.f, 100.f), 10.f);
                    }
                }
                else
                {
                    if (Overlay::bBoxes)
                    {
                        ImGui::GetBackgroundDrawList()->AddRect({ top.x - w, top.y }, { top.x + w, bottom.y }, ImColor(255.f, 255.f, 255.f));
                    }
                    
                    if (Overlay::bHealthbar)
                    {
                        float box_h = (float)fabs(bottom.y - top.y);

                        float offset = 8;

                        int height = (box_h * Entity::getEntHp(Base)) / 100;


                        int green = int(Entity::getEntHp(Base) * 2.55f);
                        int red = 255 - green;

                        int x = top.x - w - offset;
                        int y = bottom.y;
                        int w = 4;
                        int h = box_h;

                        RenderBox(x, y, x + w, y - h, ImColor(0, 0, 0), 1.f, true);
                        RenderBox(x + 1, y - 2, x + w - 1, y - height + 1, ImColor(red, green, 0, 255), 1.f, true);
                    }
                }
            }
        }

        if (Overlay::bRecoilCrosshair)
        {

            float x = Width / 2;
            float y = Height / 2;
            float dy = Height / 90;
            float dx = Width / 90;
            x -= (dx * (LocalPlayer::getLocalPunchAngles().y));
            y += (dy * (LocalPlayer::getLocalPunchAngles().x));

            ImGui::GetBackgroundDrawList()->AddCircle({ x, y }, 5.f, ImColor(255, 255, 255, RecoilCrosshair::opacity), 0, 2.f);
        }


        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            bMenuVisible = !bMenuVisible;

            if (bMenuVisible)
            {
                ShowMenu(window);
            }
            else
            {
                Hidemenu(window);
            }
        }

        //Draw here ;)
        if (bMenuVisible)
        {
            
            ImGui::Begin("Hydra", &bMenuVisible, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);

            

            //defining and making the tabs
 
		    
		    if (ImGui::Button("Aimbot", ImVec2(150, 25)))
		    {
                Overlay::iTab = 0;
		    }

            ImGui::SameLine();

            if (ImGui::Button("Triggerbot", ImVec2(150, 25)))
            {
                Overlay::iTab = 1;
            }

		    ImGui::SameLine();
 
            if (ImGui::Button("Visuals", ImVec2(150, 25)))
            {
                Overlay::iTab = 2;
            }

		    ImGui::SameLine();
		    if (ImGui::Button("Misc", ImVec2(150, 25)))
		    {
                Overlay::iTab = 3;
		    }
					


            switch (Overlay::iTab)
            {
            case 0:
            {
                ImGui::Text("Welcome to External 2.0");
                ImGui::Text("Now with multithreading!");

                ImGui::Checkbox("Enable", &Aimbot::bEnabled);
                if (Aimbot::bEnabled)
                {
                    ImGui::Text("Aim Key");
                    ImGui::SameLine();
                    ImGui::Hotkey(&Aimbot::AimKey);
                    ImGui::SliderFloat("Fov", &Aimbot::fFov, 1.f, 10.f);
                    ImGui::SliderFloat("Smoothing", &Aimbot::fSmoothing, 1.f, 10.f);

                    if (ImGui::BeginCombo("Hitbox", Aimbot::current_hitbox))
                    {
                        for (int n = 0; n < ((int)(sizeof(Aimbot::hitboxes) / sizeof(*(Aimbot::hitboxes)))); n++)
                        {
                            bool is_selected = (Aimbot::current_hitbox == Aimbot::hitboxes[n]);
                            if (ImGui::Selectable(Aimbot::hitboxes[n], is_selected))
                            {
                                Aimbot::current_hitbox = Aimbot::hitboxes[n];
                            }
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndCombo();
                    }
                }
                //TODO: STANDALONE RECOIL.
                ImGui::Checkbox("RCS", &Aimbot::bRecoil);
                if (Aimbot::bRecoil)
                {
                    ImGui::SliderFloat("Recoil X", &Aimbot::fRecoilX, 0.f, 1.f);
                    ImGui::SliderFloat("Recoil Y", &Aimbot::fRecoilY, 0.f, 1.f);
                }

                break;
            }
            case 1:
            {
                ImGui::Checkbox("Enable", &triggerbot::bTriggerEnabled);
                if (triggerbot::bTriggerEnabled)
                {
                    ImGui::Text("Trigger Key");
                    ImGui::SameLine();
                    ImGui::Hotkey(&triggerbot::TriggerKey);

                    ImGui::SliderInt("Delay Min", &triggerbot::iMinDelay, 1, 100);
                    ImGui::SliderInt("Delay Max", &triggerbot::iMaxDelay, 1, 100);
                }
                break;
            }
            case 2:
            {
                ImGui::Checkbox("Boxes", &Overlay::bBoxes);
                ImGui::Checkbox("Health Bar", &Overlay::bHealthbar);
                ImGui::Checkbox("Recoil crosshair", &Overlay::bRecoilCrosshair);
                break;
            }
            case 3:
            {
                ImGui::Checkbox("Bhop", &bhop::bBhopEnabled);
                if (bhop::bBhopEnabled)
                {
                    ImGui::SliderInt("Delay Min", &bhop::iMinDelay, 1, 100);
                    ImGui::SliderInt("Delay Max", &bhop::iMaxDelay, 1, 100);
                }

                ImGui::Checkbox("Auto pistol", &autopistol::bAutopistol);


                if (ImGui::Button("Exit"))
                {
                    exit(0);
                }
                auto fps = ImGui::GetIO().Framerate;

                char buffer[64];
                int ret = snprintf(buffer, sizeof buffer, "%f", fps);

                if (ret < 0) {
                    return EXIT_FAILURE;
                }
                if (ret >= sizeof buffer) {
                    /* Result was truncated - resize the buffer and retry.*/
                }

                ImGui::Text(buffer);
                break;
            }
            default:
                break;
            }

            ImGui::End();
        }


        ImGui::Render();

        constexpr float clear_color[4] = { 0.f, 0.f, 0.f, 0.f };
        device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
        device_context->ClearRenderTargetView(render_target_view, clear_color);

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        swap_chain->Present(1U, 0U);

    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (swap_chain) {
        swap_chain->Release();
        swap_chain = nullptr;
    }

    if (device_context) {
        device_context->Release();
        device_context = nullptr;
    }

    if (device) {
        device->Release();
        device = nullptr;
    }

    if (render_target_view) {
        render_target_view->Release();
        render_target_view = nullptr;
    }

    DestroyWindow(window);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return TRUE;
}