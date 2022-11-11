#include "RecoilCrosshair.hpp"

void RecoilCrosshair::init()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (LocalPlayer::getShotsFired() && Overlay::bRecoilCrosshair && opacity < 255)
        {
            opacity++;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        while (!LocalPlayer::getShotsFired() && Overlay::bRecoilCrosshair && opacity > -1)
        {
            opacity--;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}