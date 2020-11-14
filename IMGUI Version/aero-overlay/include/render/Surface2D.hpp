#pragma once
#ifndef REACTIION_AERO_OVERLAY_SURFACE2D_HPP
#define REACTIION_AERO_OVERLAY_SURFACE2D_HPP

#include "Surface.hpp"
#include "Font2D.hpp"

namespace render {

class Surface2D :
    public Surface
{
public:
    ///-------------------------------------------------------------------------------------------------
    /// Default constructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    Surface2D() = default;

    ///-------------------------------------------------------------------------------------------------
    /// Constructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  write_factory   The write factory.
    /// @param  color_brush     The color brush.
    ///-------------------------------------------------------------------------------------------------
    Surface2D( 
        const IDWriteFactory*       write_factory,
        const ID2D1SolidColorBrush* color_brush );

    ///-------------------------------------------------------------------------------------------------
    /// Destructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    ~Surface2D() override;
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
        const void*                device ) override;

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
        const std::string&          name,
        const std::string&          definition,
        const int32_t               height,
        const int32_t               weight,
        const int32_t               flags ) override;

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
        const int32_t                x,
        const int32_t                y,
        const Font_t&                font,
        const drawing::Color&        color,
        const std::string&           message) override;

    ///-------------------------------------------------------------------------------------------------
    /// Sets render target.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  render_target   The render target.
    ///-------------------------------------------------------------------------------------------------
    void   set_render_target(
        const ID2D1HwndRenderTarget* render_target );

    ///-------------------------------------------------------------------------------------------------
    /// Sets write factory.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  write_factory   The write factory.
    ///-------------------------------------------------------------------------------------------------
    void   set_write_factory(
        const IDWriteFactory*        write_factory );

    ///-------------------------------------------------------------------------------------------------
    /// Sets color brush.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  color_brush The color brush.
    ///-------------------------------------------------------------------------------------------------
    void   set_color_brush(
        const ID2D1SolidColorBrush*  color_brush );

protected:
    ///-------------------------------------------------------------------------------------------------
    /// Renders the data.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    void   render_data() override;

private:
    /// The Direct2D render target.
    ID2D1HwndRenderTarget* m_Direct2DHwndRenderTarget = nullptr;
    /// The DirectWrite factory.
    IDWriteFactory*        m_DirectWriteFactory = nullptr;
    /// The Direct2D color brush.
    ID2D1SolidColorBrush*  m_Diect2DColorBrush = nullptr;
};

}

#endif
