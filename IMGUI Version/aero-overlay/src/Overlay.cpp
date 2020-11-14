#include <render/Overlay.hpp>
#include <render/Device2D.hpp>
#include <render/Device3D9.hpp>
using namespace render;

Overlay::Overlay()
{
    m_ClassName.assign( generate_random_string( 128 ) );
    m_WindowTitle.assign( generate_random_string( 128 ) );
}

Overlay::~Overlay()
{
}

bool Overlay::create(
    const std::string& target_window_title )
{
    if( target_window_title.empty() ) {
        return false;
    }

    std::unique_lock<Mutex> lock( m_mutex );
    HWND tWnd = tWnd = FindWindow(0, L"Gameloop【Turbo AOW Engine-4.4】");
    m_WndTarget = FindWindowEx(tWnd, NULL, L"AEngineRenderWindowClass", NULL);
    if( !m_WndTarget ) {
        return false;
    }

#if defined(_UNICODE)
    const auto class_name   = convert_string_to_wide( m_ClassName );
    const auto window_title = convert_string_to_wide( m_WindowTitle );
#endif

    WNDCLASSEX window_class_ex =
    {
        sizeof( WNDCLASSEX ),
        0,
        window_procedure,
        0,
        0,
        nullptr,
        LoadIcon( nullptr, IDI_APPLICATION ),
        LoadCursor( nullptr, IDC_ARROW ),
        nullptr,
        nullptr,
    #if defined(_UNICODE)
        class_name.c_str(),
    #else
        m_ClassName.c_str(),
    #endif 
        LoadIcon( nullptr, IDI_APPLICATION )
    };

    if( !RegisterClassEx( &window_class_ex ) ) {
        return false;
    }

    m_WndOverlay = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
    #ifdef _UNICODE
        class_name.c_str(),
        window_title.c_str(),
    #else
        m_ClassName.c_str(),
        m_WindowTitle.c_str(),
    #endif
        WS_POPUP,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        nullptr, 
        nullptr, 
        nullptr, 
        nullptr 
    );

    if( !m_WndOverlay ) {
        return false;
    }
    /*if( !SetLayeredWindowAttributes( 
        m_WndOverlay,
        RGB( NULL, NULL, NULL ),
        255,
        ULW_COLORKEY | LWA_ALPHA ) ) {
        return false;
    }*/

	// ------------ Windows 10 RS2 Lag Fix ------------
	if (!SetLayeredWindowAttributes(
		m_WndOverlay,
		RGB(NULL, NULL, NULL),
		255,
		LWA_ALPHA)) {
		return false;
	}

	DWM_BLURBEHIND blur;
	blur.fEnable = TRUE;
	blur.dwFlags = DWM_BB_ENABLE;
	DwmEnableBlurBehindWindow(m_WndOverlay, &blur);
	// ------------------------------------------------

    auto window_props = get_window_props( m_WndTarget );    
    if( FAILED( DwmExtendFrameIntoClientArea(
        m_WndOverlay,
        reinterpret_cast<const MARGINS*>( &window_props ) )
    ) ) {
        return false;
    }

    ShowWindow( m_WndOverlay, SW_SHOWDEFAULT );
    if( !UpdateWindow( m_WndOverlay ) ) {
        return false;
    }

    scale_overlay();
    return true;
}

bool Overlay::in_foreground() const
{
    return m_WndTarget && GetForegroundWindow() == m_WndTarget;
}

bool Overlay::render()
{
    MSG current_message;
    if( PeekMessage( &current_message, nullptr, 0, 0, PM_REMOVE ) ) {
        if( current_message.message == WM_QUIT ) {
            return false;
        }

        TranslateMessage( &current_message );
        DispatchMessage( &current_message );
    }
    return true;
}

Overlay::Overlay_t Overlay::New( const EDeviceType device_type )
{
    switch( device_type ) {
    case EDeviceType::Direct2D:
        return std::make_unique<Device2D>();
    case EDeviceType::Direct3D9:
        return std::make_unique<Device3D9>();
    default:
        break;
    }
    return nullptr;
}

Overlay::RenderCallback* Overlay::add_callback(
    const std::string& name,
    RenderCallbackFn   callback,
    const bool         active )
{
    if( name.empty() || !callback ) {
        return nullptr;
    }
    
    std::unique_lock<std::shared_timed_mutex> lock( m_mutex );
    if( m_RenderCallbacks.count( name ) != 0 ) {
        return nullptr;
    }
    
    m_RenderCallbacks.insert(
        std::make_pair(
            name,
            std::make_tuple(
                callback,
                active
            )
        )
    );

    return &m_RenderCallbacks.at( name );
}

bool Overlay::pause_callback(
    const std::string& name )
{
    std::unique_lock<std::shared_timed_mutex> lock( m_mutex );
    if( !m_RenderCallbacks.count( name ) ) {
        return false;
    }

    std::get<1>( m_RenderCallbacks.at( name ) ) = false;
    return true;
}

bool Overlay::remove_callback(
    const std::string& name )
{
    if( !m_RenderCallbacks.count( name ) ) {
        return false;
    }

    m_RenderCallbacks.erase( name );
    return true;
}

bool Overlay::resume_callback(
    const std::string& name )
{
    if( !m_RenderCallbacks.count( name ) ) {
        return false;
    }

    std::get<1>( m_RenderCallbacks.at( name ) ) = true;
    return true;
}

void Overlay::scale_overlay()
{      
    auto fix_var = []( int32_t& in, int32_t& fix )
    {
        if( in == 0 ) {
            --in;
            ++fix;
        }
    };

    auto window_props = get_window_props( m_WndTarget );
    m_Width  = window_props.at( 2 );
    m_Height = window_props.at( 3 );    

    /// if we are on point 0, increase size and decrease position
    /// usefull for games like black ops 2
    fix_var( window_props.at( 0 ), m_Width );
    fix_var( window_props.at( 1 ), m_Height );

    MoveWindow(
        m_WndOverlay,
        window_props.at( 0 ),
        window_props.at( 1 ),
        m_Width,
        m_Height,
        TRUE
    );
}

void Overlay::shutdown()
{
    std::unique_lock<Mutex> lock( m_mutex );

#if defined(_UNICODE)
    UnregisterClass( convert_string_to_wide( m_ClassName ).c_str(), nullptr );
#else
    UnregisterClass( m_ClassName.c_str(), nullptr );
#endif
    if( m_WndOverlay ) {
        DestroyWindow( m_WndOverlay );
        m_WndOverlay = nullptr;
    }
    m_WndTarget = nullptr;
}

void Overlay::execute_callbacks()
{
    for( const auto& kp : m_RenderCallbacks ) {
        if( !std::get<1>( kp.second ) ) {
            continue;
        }
        std::get<0>( kp.second )( m_Surface.get() );
    }
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT Overlay::window_procedure(
    HWND   window,
    UINT   message,
    WPARAM wparam,
    LPARAM lparam )
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wparam, lparam))
		return true;

    switch( message ) {
    case WM_DESTROY:
        PostQuitMessage( EXIT_SUCCESS );
        return 0;
    case WM_KEYDOWN:
        return 0;
    case WM_ERASEBKGND:
        SendMessage( window, WM_PAINT, 0, 0 );
        return TRUE;
    case WM_PAINT:
        return 0;
    default:
        break;
    }
    return DefWindowProc( 
        window,
        message,
        wparam,
        lparam
    );
}

Overlay::WindowProps Overlay::get_window_props( HWND window )
{
    static WindowProps props;
    if( window ) {
        static POINT difference;
        static RECT rect_client, rect_window;
        difference = { 0, 0 };


        GetClientRect( window, &rect_client );
        props.at( 2 ) = rect_client.right;
        props.at( 3 ) = rect_client.bottom;


        GetWindowRect( window, &rect_window );
        difference = { 0, 0 };

        ClientToScreen( window, &difference );
        props.at( 0 ) = rect_window.left + ( difference.x - rect_window.left );
        props.at( 1 ) = rect_window.top + ( difference.y - rect_window.top );
    }
    return props;
}

std::string Overlay::generate_random_string( const size_t length )
{
    static std::string alpha_numeric_chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<size_t> dis( 0U, alpha_numeric_chars.size() - 1U );

    std::string random_string( "", length );
    for( size_t i = 0; i < length; ++i ) {
        random_string.at( i ) = alpha_numeric_chars.at( dis( gen ) );
    }

    return random_string;
}

std::wstring Overlay::convert_string_to_wide( const std::string& str )
{
    static std::wstring_convert<
        std::codecvt_utf8_utf16<wchar_t>
    > converter;

    return converter.from_bytes( str );
}
Vector3 Overlay::AimPredition(Vector3 Me ,Vector3 Target,Vector3 TargetSpeed,float bulletSpeed)
{
    Vector3 aimPosition = Target;
    float x = (TargetSpeed.x - g_pEsp->MyVelocity.x);
    float y = (TargetSpeed.y - g_pEsp->MyVelocity.y);
    if(x != 0|| y != 0)
    aimPosition.x = Target.x + ( x / bulletSpeed);
    aimPosition.y = Target.x + ( x / bulletSpeed);

    return aimPosition;
}
void Overlay::AimFindBestTarget(std::vector<playerData> playerdatar) {
    float targetDistance = 9999.0;
    int dist;
    if (playerdatar.size() == 0)
    {
        g_pAimbot->aimtarget.x = 0;
        g_pAimbot->aimtarget.y = 0;
        g_pAimbot->aimplayer = -1;
        return;
    }
    for (int i = 0; i < playerdatar.size(); i++) {
        DWORD tmpAddv = g_pMemoryManager->iRead(playerdatar[i].Address + 776);
        DWORD bodyAddv = tmpAddv + 320;
        DWORD boneAddv = g_pMemoryManager->iRead(tmpAddv + 1408) + 48;

        Vector2 chest;
        Vector3 chestPos;
        if (g_pAimbot->aimtype)
            chestPos = GetBoneWorldPosition(bodyAddv, boneAddv + 4 * 48); //Neak
        else
            chestPos = GetBoneWorldPosition(bodyAddv, boneAddv + 1 * 48); // Chest
        if (WorldToScreenBone(g_pEsp->vt, chestPos, chest, &dist))
        {
            if (playerdatar[i].Health > 0) {
                float cross_dist = sqrt(pow(chest.x - m_Width / 2, 2) + pow(chest.y - m_Height / 2, 2));
                if (cross_dist < targetDistance)
                {
                    g_pAimbot->magicaim = chestPos;
                    g_pAimbot->aimtarget = chest;
                    targetDistance = cross_dist;
                    g_pAimbot->aimplayer = i;
                }
            }
        }
    }
}

bool Overlay::WorldToScreen(Vector3 pos, Vector3 & screen, int* distance, D3DMatrix viewMatrix) {
    float screenW = (viewMatrix._14 * pos.x) + (viewMatrix._24 * pos.y) + (viewMatrix._34 * pos.z + viewMatrix._44);
    screen.z = screenW;
    *distance = (screenW / 100);
    if (screenW < 0.0001f) return false;
    screenW = 1 / screenW;
    float sightX = (m_Width / 2);
    float sightY = (m_Height / 2);
    screen.x = sightX + (viewMatrix._11 * pos.x + viewMatrix._21 * pos.y + viewMatrix._31 * pos.z + viewMatrix._41) * screenW * sightX;
    screen.y = sightY - (viewMatrix._12 * pos.x + viewMatrix._22 * pos.y + viewMatrix._32 * pos.z + viewMatrix._42) * screenW * sightY;
    return true;
}
bool Overlay::WorldToScreenBone(D3DMatrix viewMatrix, Vector3 pos, Vector2& screen, int* distance) {
    float screenW = (viewMatrix._14 * pos.x) + (viewMatrix._24 * pos.y) + (viewMatrix._34 * pos.z + viewMatrix._44);
    *distance = (screenW / 100);
    if (screenW < 0.0001f) return false;
    screenW = 1 / screenW;
    float sightX = (m_Width / 2);
    float sightY = (m_Height / 2);
    screen.x = sightX + (viewMatrix._11 * pos.x + viewMatrix._21 * pos.y + viewMatrix._31 * pos.z + viewMatrix._41) * screenW * sightX;
    screen.y = sightY - (viewMatrix._12 * pos.x + viewMatrix._22 * pos.y + viewMatrix._32 * pos.z + viewMatrix._42) * screenW * sightY;
    return true;
}
bool Overlay::WorldToScreenPlayer(Vector3 pos, Vector3& screen, int* distance, D3DMatrix viewMatrix) {
    float screenW = (viewMatrix._14 * pos.x) + (viewMatrix._24 * pos.y) + (viewMatrix._34 * pos.z + viewMatrix._44);
    *distance = (screenW / 100);
    if (screenW < 0.0001f) return false;
    float screenY = (viewMatrix._12 * pos.x) + (viewMatrix._22 * pos.y) + (viewMatrix._32 * (pos.z + 85) + viewMatrix._42);
    float screenX = (viewMatrix._11 * pos.x) + (viewMatrix._21 * pos.y) + (viewMatrix._31 * pos.z + viewMatrix._41);
    screen.y = (m_Height / 2) - (m_Height / 2) * screenY / screenW;
    screen.x = (m_Width / 2) + (m_Width / 2) * screenX / screenW;
    float y1 = (m_Height / 2) - (viewMatrix._12 * pos.x + viewMatrix._22 * pos.y + viewMatrix._32 * (pos.z - 95) + viewMatrix._42) * (m_Height / 2) / screenW;
    screen.z = y1 - screen.y;
    return true;
}
D3DMatrix Overlay::ToMatrixWithScale(Vector3 translation, Vector3 scale, Vector4 rot) {
    D3DMatrix m;
    m._41 = translation.x;
    m._42 = translation.y;
    m._43 = translation.z;

    float x2 = rot.x + rot.x;
    float y2 = rot.y + rot.y;
    float z2 = rot.z + rot.z;

    float xx2 = rot.x * x2;
    float yy2 = rot.y * y2;
    float zz2 = rot.z * z2;
    m._11 = (1.0f - (yy2 + zz2)) * scale.x;
    m._22 = (1.0f - (xx2 + zz2)) * scale.y;
    m._33 = (1.0f - (xx2 + yy2)) * scale.z;

    float yz2 = rot.y * z2;
    float wx2 = rot.w * x2;
    m._32 = (yz2 - wx2) * scale.z;
    m._23 = (yz2 + wx2) * scale.y;

    float xy2 = rot.x * y2;
    float wz2 = rot.w * z2;
    m._21 = (xy2 - wz2) * scale.y;
    m._12 = (xy2 + wz2) * scale.x;

    float xz2 = rot.x * z2;
    float wy2 = rot.w * y2;
    m._31 = (xz2 + wy2) * scale.z;
    m._13 = (xz2 - wy2) * scale.x;

    m._14 = 0.0f;
    m._24 = 0.0f;
    m._34 = 0.0f;
    m._44 = 1.0f;

    return m;
}
D3DMatrix Overlay::MatrixMultiplication(D3DMatrix pM1, D3DMatrix pM2) {
    D3DMatrix pOut = {
        pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41,
        pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42,
        pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43,
        pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44,
        pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41,
        pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42,
        pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43,
        pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44,
        pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41,
        pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42,
        pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43,
        pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44,
        pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41,
        pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42,
        pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43,
        pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44
    };

    return pOut;
}
Vector3 Overlay::GetBoneWorldPosition(DWORD actorAddv, DWORD boneAddv) {
    FTTransform2_t bone = g_pMemoryManager->ReadFTransform2(boneAddv);
    FTTransform2_t actor = g_pMemoryManager->ReadFTransform2(actorAddv);
    D3DMatrix boneMatrix = ToMatrixWithScale(bone.Translation, bone.Scale3D, bone.Rotation);
    D3DMatrix componentToWorldMatrix = ToMatrixWithScale(actor.Translation, actor.Scale3D, actor.Rotation);
    D3DMatrix newMatrix = MatrixMultiplication(boneMatrix, componentToWorldMatrix);
    Vector3 bonePos;
    bonePos.x = newMatrix._41;
    bonePos.y = newMatrix._42;
    bonePos.z = newMatrix._43;
    return bonePos;
}
bool Overlay::isnull(Vector2 dat)
{
    if (dat.x != NULL)
        if (dat.y != NULL)
            return true;
    return false;
}
