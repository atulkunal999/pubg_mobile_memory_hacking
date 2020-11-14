#pragma once
#ifndef REACTIION_AERO_OVERLAY_OVERLAY_HPP
#define REACTIION_AERO_OVERLAY_OVERLAY_HPP
#include "Surface.hpp"
#include "../hacks/pch.h"
namespace render {

enum class EDeviceType
{
    ///< Direct2D + Direct Draw
    Direct2D = 0,

    ///< DirectX 9
    Direct3D9,
};

class Overlay
{
    /// An alias for the mutex.
    using Mutex            = std::shared_timed_mutex;
public:
    /// An alias for the unique surface pointer.
    using Surface_t        = std::unique_ptr<Surface>;
    /// An alias for the unique overlay pointer.
    using Overlay_t        = std::unique_ptr<Overlay>;
    /// An alias for the window properties.
    ///< 0: x position
    ///< 1: y position
    ///< 2: width
    ///< 3: height
    using WindowProps      = std::array<int32_t, 4>;
    /// A typedef for the render callback function.
    using RenderCallbackFn = void( *)( Surface* surface );
    /// An alias for the render callback data.
    using RenderCallback   = std::tuple<RenderCallbackFn, bool>;
    /// An alias for the map of render callbacks.
    using RenderCallbacks  = std::map<std::string, RenderCallback>;

public:
    ///-------------------------------------------------------------------------------------------------
    /// Default constructor.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///-------------------------------------------------------------------------------------------------
    Overlay();

    ///-------------------------------------------------------------------------------------------------
    /// Destructor.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual ~Overlay();

    ///-------------------------------------------------------------------------------------------------
    /// Creates a new bool.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  target_window_title Target window title.
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool            create(
        const std::string& target_window_title );

    bool WorldToScreen(Vector3 pos, Vector3& screen, int* distance, D3DMatrix viewMatrix);
    bool WorldToScreenBone(D3DMatrix viewMatrix, Vector3 pos, Vector2& screen, int* distance);
    bool WorldToScreenPlayer(Vector3 pos, Vector3& screen, int* distance, D3DMatrix viewMatrix);
    D3DMatrix ToMatrixWithScale(Vector3 translation, Vector3 scale, Vector4 rot);
    D3DMatrix MatrixMultiplication(D3DMatrix pM1, D3DMatrix pM2);
    Vector3 GetBoneWorldPosition(DWORD actorAddv, DWORD boneAddv);
    void AimFindBestTarget(std::vector<playerData> playerdatar);
    bool isnull(Vector2 dat);
    Vector3 AimPredition(Vector3 Me, Vector3 Target, Vector3 TargetSpeed, float bulletSpeed);
    ///-------------------------------------------------------------------------------------------------
    /// Determines if we can in foreground.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool            in_foreground() const;

    ///-------------------------------------------------------------------------------------------------
    /// Renders this object.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool            render();

    ///-------------------------------------------------------------------------------------------------
    /// Gets the surface.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @return Null if it fails, else the surface.
    ///-------------------------------------------------------------------------------------------------
    inline Surface*         get_surface() const;

    ///-------------------------------------------------------------------------------------------------
    /// News the given device type.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  device_type Type of the device.
    ///
    /// @return An Overlay_t.
    ///-------------------------------------------------------------------------------------------------
    static Overlay_t        New( const EDeviceType device_type );

    virtual RenderCallback* add_callback(
        const std::string& name,
        RenderCallbackFn   callback,
        const bool         active = true );

    ///-------------------------------------------------------------------------------------------------
    /// Callback, called when the pause.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  name    The name.
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool            pause_callback( const std::string& name );

    ///-------------------------------------------------------------------------------------------------
    /// Removes the callback described by name.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  name    The name.
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool            remove_callback( const std::string& name );

    ///-------------------------------------------------------------------------------------------------
    /// Callback, called when the resume.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  name    The name.
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool            resume_callback( const std::string& name );

    ///-------------------------------------------------------------------------------------------------
    /// Scales the overlay size to the target window size.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual void            scale_overlay();

    ///-------------------------------------------------------------------------------------------------
    /// Shuts down this object and frees any resources it is using.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual void            shutdown();

protected:
    ///-------------------------------------------------------------------------------------------------
    /// Executes the callbacks operation.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual void            execute_callbacks();

    ///-------------------------------------------------------------------------------------------------
    /// Window procedure.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  window  Handle of the window.
    /// @param  message The message.
    /// @param  wparam  The wParam field of the message.
    /// @param  lparam  The lParam field of the message.
    ///
    /// @return A CALLBACK.
    ///-------------------------------------------------------------------------------------------------
    static LRESULT CALLBACK window_procedure(
        HWND               window,
        UINT               message,
        WPARAM             wparam,
        LPARAM             lparam );

    ///-------------------------------------------------------------------------------------------------
    /// Gets window properties.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  window  Handle of the window.
    ///
    /// @return The window properties.
    ///-------------------------------------------------------------------------------------------------
    static WindowProps      get_window_props( 
        HWND               window );
public:
    ///-------------------------------------------------------------------------------------------------
    /// Generates a random string.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  length  The length.
    ///
    /// @return The random string.
    ///-------------------------------------------------------------------------------------------------
    static std::string      generate_random_string( 
        const size_t       length );

    ///-------------------------------------------------------------------------------------------------
    /// Convert string to wide.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  str The string.
    ///
    /// @return The string converted to wide.
    ///-------------------------------------------------------------------------------------------------
    static std::wstring     convert_string_to_wide( 
        const std::string& str );

public:
    /// Handle of the overlay window.
    HWND            m_WndOverlay = nullptr;
    /// Handle of the target window.
    HWND            m_WndTarget  = nullptr;
    /// The width.
    int32_t         m_Width      = 0;
    /// The height.
    int32_t         m_Height     = 0;
    /// Name of the class.
    std::string     m_ClassName;
    /// The window title.
    std::string     m_WindowTitle;
    /// The surface.
    Surface_t       m_Surface;
    /// The render callbacks.
    RenderCallbacks m_RenderCallbacks;
    /// The mutex.
    mutable Mutex   m_mutex;
};

inline Surface* Overlay::get_surface() const
{
    return m_Surface ? m_Surface.get() : nullptr;
}

}

#endif
