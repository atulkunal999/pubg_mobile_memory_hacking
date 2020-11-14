#include <render/Device2D.hpp>
#include <render/Device3D9.hpp>
#include "../hacks/pch.h"
using namespace render;

std::unique_ptr<Overlay> create_overlay( const EDeviceType type, const std::string& window_title )
{
    auto overlay = Overlay::New( type );
    if( !overlay ) {
        return nullptr;
    }
    if( !overlay->create( window_title ) ) {
        return nullptr;
    }

    auto surface = overlay->get_surface();
    if( !surface ) {
        return nullptr;
    }

    const auto is_d3d9 = type == EDeviceType::Direct3D9;

    if (!surface->add_font(
        "12",
        "Segoe UI",
        is_d3d9 ? 12 : 9,
        is_d3d9 ? FW_HEAVY : DWRITE_FONT_WEIGHT_NORMAL,
        /// or DEFAULT_QUALITY instead of PROOF_QUALITY for anti aliasing
        is_d3d9 ? PROOF_QUALITY : DWRITE_FONT_STRETCH_NORMAL
    )) {
        return nullptr;
    }
    if (!surface->add_font(
        "13",
        "Segoe UI",
        is_d3d9 ? 13 : 10,
        is_d3d9 ? FW_HEAVY : DWRITE_FONT_WEIGHT_NORMAL,
        /// or DEFAULT_QUALITY instead of PROOF_QUALITY for anti aliasing
        is_d3d9 ? PROOF_QUALITY : DWRITE_FONT_STRETCH_NORMAL
    )) {
        return nullptr;
    }
    if( !surface->add_font(
        "14",
        "Segoe UI",
        is_d3d9 ? 14 : 11,
        is_d3d9 ? FW_HEAVY : DWRITE_FONT_WEIGHT_NORMAL,
        /// or DEFAULT_QUALITY instead of PROOF_QUALITY for anti aliasing
        is_d3d9 ? PROOF_QUALITY : DWRITE_FONT_STRETCH_NORMAL
    ) ) {
        return nullptr;
    }
    if (!surface->add_font(
        "15",
        "Segoe UI",
        is_d3d9 ? 15 : 12,
        is_d3d9 ? FW_HEAVY : DWRITE_FONT_WEIGHT_NORMAL,
        /// or DEFAULT_QUALITY instead of PROOF_QUALITY for anti aliasing
        is_d3d9 ? PROOF_QUALITY : DWRITE_FONT_STRETCH_NORMAL
    )) {
        return nullptr;
    }
    if (!surface->add_font(
        "18",
        "Segoe UI",
        is_d3d9 ? 18 : 14,
        is_d3d9 ? FW_HEAVY : DWRITE_FONT_WEIGHT_NORMAL,
        /// or DEFAULT_QUALITY instead of PROOF_QUALITY for anti aliasing
        is_d3d9 ? PROOF_QUALITY : DWRITE_FONT_STRETCH_NORMAL
    )) {
        return nullptr;
    }

    return std::move( overlay );
}
void initall()
{
    int ProcessId = ProcManager::getAowProcID();
    if (!ProcessId)
    {
        MessageBox(0, L"SONIC LOOP Not Found Exiting...", L"Error", MB_OK);
        exit(1);
    }
    g_pMemoryManager->init(ProcessId, true);
    if (!g_pMemoryManager->DriverLoaded) {
        MessageBox(0, L"Error Loading Driver", L"Error", MB_OK);
        exit(1);
    }
    g_pEsp->viewWordBase = g_pEsp->getViewWorld();
    //g_pEsp->GetModuleBaseAddress(ProcessId, "aow_exe.exe");
    
    /*IF YOU NEED MAGIC THEN DONATE FOR FURTHER DEVLOPMENT I NEED TO UPDATE DRIVER ALSO FOR THAT & THIS IS DEMO NOT WORKING*/
    //g_pEsp->GetMagic();
    //g_pEsp->initMagic();

    //THIS BOTH WORKING IN SMARTGAGA
    //g_pEsp->ipadview();
    //g_pEsp->initBoost();
    g_pEsp->init();
}
void updateesp()
{
    while (1)
    {
        g_pEsp->update();
    }
}

void updateaim()
{
    while (1)
    {
        if (g_pAimbot->aimbot)
        {
            g_pAimbot->updateaim();
        }
        if (g_pAimbot->boostenabled)
        {
            g_pAimbot->Boostplayer();
        }
        g_pAimbot->IpadV();
    }
}
int32_t main( int32_t argc, char** argv )
{
    //USE X64 DEBUG OR RELESE VERSION ONLY
    initall();
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)updateesp, 0, 0, 0);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)updateaim, 0, 0, 0);

    std::unique_ptr<Overlay> overlay = nullptr;
    overlay = create_overlay( EDeviceType::Direct3D9, "RIXOT ALWAYS OP" );
    auto* callback = overlay->add_callback(
        "show", []( Surface* surface ) {
       }
    );
    if( !callback ) {
        return EXIT_FAILURE;
    }
    
    while( overlay->render() ) {
		overlay->scale_overlay();
        std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    }

    overlay->shutdown();
    return EXIT_SUCCESS;
}
