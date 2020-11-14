#pragma once
#ifndef REACTIION_AERO_OVERLAY_SURFACE3D9_HPP
#define REACTIION_AERO_OVERLAY_SURFACE3D9_HPP

#include "Surface.hpp"
#include "Font3D9.hpp"

namespace render {

class Surface3D9 :
    public Surface
{
public:
    ///-------------------------------------------------------------------------------------------------
    /// Default constructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    Surface3D9() = default;

    ///-------------------------------------------------------------------------------------------------
    /// Constructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  sprite  The sprite.
    ///-------------------------------------------------------------------------------------------------
    Surface3D9( 
        const ID3DXSprite*  sprite );

    ///-------------------------------------------------------------------------------------------------
    /// Destructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    ~Surface3D9() override;

    ///-------------------------------------------------------------------------------------------------
    /// Initializes this object.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  device  The device.
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    bool   initialize(
        const void*          device ) override;

    ///-------------------------------------------------------------------------------------------------
    /// Begins a scene.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    bool   begin_scene() override;

    ///-------------------------------------------------------------------------------------------------
    /// Adds a font.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  name        The name.
    /// @param  definition  The definition.
    /// @param  height      The height.
    /// @param  weight      The weight.
    /// @param  flags       The flags.
    ///
    /// @return A Font_t.
    ///-------------------------------------------------------------------------------------------------
    Font_t add_font(
        const std::string&   name,
        const std::string&   definition,
        const int32_t        height,
        const int32_t        weight,
        const int32_t        flags ) override;

    ///-------------------------------------------------------------------------------------------------
    /// Ends a scene.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    void   end_scene() override;

    ///-------------------------------------------------------------------------------------------------
    /// Shuts down this object and frees any resources it is using.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    void   shutdown() override;

    ///-------------------------------------------------------------------------------------------------
    /// Texts.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  x       The int32_t to process.
    /// @param  y       The int32_t to process.
    /// @param  font    The font.
    /// @param  color   The color.
    /// @param  message The message.
    ///-------------------------------------------------------------------------------------------------
    void   text(
        const int32_t         x,
        const int32_t         y,
        const Font_t&         font,
        const drawing::Color& color,
        const std::string&    message ) override;

    ///-------------------------------------------------------------------------------------------------
    /// Sets a sprite.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  sprite  The sprite.
    ///-------------------------------------------------------------------------------------------------
    void   set_sprite( const ID3DXSprite* sprite );

protected:
    ///-------------------------------------------------------------------------------------------------
    /// Renders the data.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    void   render_data() override;

private:
    /// The DirectX9 device.
    IDirect3DDevice9Ex* m_Direct3D9Device = nullptr;

    /// The DirectX sprite.
    ID3DXSprite*        m_Direct3DXSprite = nullptr;
};

}

#endif
