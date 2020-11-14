#pragma once
#ifndef REACTIION_AERO_OVERLAY_DEVICE3D9_HPP
#define REACTIION_AERO_OVERLAY_DEVICE3D9_HPP

#include "Overlay.hpp"
#include "Surface3D9.hpp"

namespace render {

class Device3D9 :
    public Overlay
{
public:
    ///-------------------------------------------------------------------------------------------------
    /// Default constructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    Device3D9() = default;

    ///-------------------------------------------------------------------------------------------------
    /// Destructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    ~Device3D9() override;

    ///-------------------------------------------------------------------------------------------------
    /// Creates a new bool.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  target_window_title Target window title.
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    bool create( 
        const std::string& target_window_title ) override;
    void DrawTriangle(Vector2 a, Vector2 b, Vector2 c, drawing::Color col);
    void DrawPlayerBlood(float x, float y, float h, float w, float fBlood, int max);

    ///-------------------------------------------------------------------------------------------------
    /// Renders this object.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    bool render() override;
    ///-------------------------------------------------------------------------------------------------
    /// Shuts down this object and frees any resources it is using.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    void shutdown() override;

private:
    /// The DirectX9 interface.
    IDirect3D9Ex*       m_Direct3D9Ex     = nullptr;
    /// The DirectX9 device.
    IDirect3DDevice9Ex* m_Direct3D9Device = nullptr;
    /// The DirectX sprite.
    ID3DXSprite*        m_Direct3DXSprite = nullptr;
};

}

#endif
