#pragma once
#ifndef REACTIION_AERO_OVERLAY_FONT3D9_HPP
#define REACTIION_AERO_OVERLAY_FONT3D9_HPP

/// the Font interface
#include "Font.hpp"

/// DirectX 9 includes
#include <d3d9.h>
#include <d3dx9.h>

/// link the libraries for DirectX 9
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

namespace render {

class Font3D9 :
    public Font
{
public:
    ///-------------------------------------------------------------------------------------------------
    /// Default constructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    Font3D9() = default;

    ///-------------------------------------------------------------------------------------------------
    /// Constructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  name    The name.
    /// @param  height  The height.
    /// @param  weight  The weight.
    /// @param  flags   The flags.
    /// @param  device  The device.
    ///-------------------------------------------------------------------------------------------------
    Font3D9(
        const std::string&        name,
        const int32_t             height,
        const int32_t             weight,
        const int32_t             flags,
        const IDirect3DDevice9Ex* device );

    ///-------------------------------------------------------------------------------------------------
    /// Destructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    ~Font3D9() override;

    ///-------------------------------------------------------------------------------------------------
    /// Shuts down this object and frees any resources it is using.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    void       shutdown() override;

    ///-------------------------------------------------------------------------------------------------
    /// Creates a new bool.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    bool       create() override;

    ///-------------------------------------------------------------------------------------------------
    /// Gets the font.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @return Null if it fails, else the font.
    ///-------------------------------------------------------------------------------------------------
    ID3DXFont* get_font() const;

    ///-------------------------------------------------------------------------------------------------
    /// Sets a device.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  device  The device.
    ///-------------------------------------------------------------------------------------------------
    void       set_device( 
        const IDirect3DDevice9Ex* device );    

protected:
    /// The DirectX9 device.
    IDirect3DDevice9Ex* m_Direct3D9Device = nullptr;
    /// The DirectX font.
    ID3DXFont*          m_Direct3DXFont   = nullptr;
};

}

#endif
