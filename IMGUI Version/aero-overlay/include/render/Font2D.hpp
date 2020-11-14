#pragma once
#ifndef REACTIION_AERO_OVERLAY_FONT2D_HPP
#define REACTIION_AERO_OVERLAY_FONT2D_HPP

/// the Font interface
#include "Font.hpp"

/// disable the compiler warning C4005
/// mixing DirectX with Direct2D will result in a ton of
/// compiler warnings (previous definition XXX)
#pragma warning( disable : 4005 )
/// Direct2D + Direct Draw include files
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

/// link the libraries for Direct2D + Direct Draw
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )

/// enable the compiler warning C4005
#pragma warning( default : 4005 )

namespace render {

class Font2D :
    public Font
{
public:
    ///-------------------------------------------------------------------------------------------------
    /// Default constructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    Font2D() = default;

    ///-------------------------------------------------------------------------------------------------
    /// Constructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  name            The name.
    /// @param  height          The height.
    /// @param  weight          The weight.
    /// @param  flags           The flags.
    /// @param  write_factory   The write factory.
    ///-------------------------------------------------------------------------------------------------
    Font2D( 
        const std::string&    name,
        const int32_t         height,
        const int32_t         weight,
        const int32_t         flags,
        const IDWriteFactory* write_factory );

    ///-------------------------------------------------------------------------------------------------
    /// Destructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    ~Font2D() override;

    ///-------------------------------------------------------------------------------------------------
    /// Shuts down this object and frees any resources it is using.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    void               shutdown() override;

    ///-------------------------------------------------------------------------------------------------
    /// Creates a new bool.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    bool               create() override;

    ///-------------------------------------------------------------------------------------------------
    /// Gets the font.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @return Null if it fails, else the font.
    ///-------------------------------------------------------------------------------------------------
    IDWriteTextFormat* get_font() const;

    ///-------------------------------------------------------------------------------------------------
    /// Sets a device.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///
    /// @param  write_factory   The write factory.
    ///-------------------------------------------------------------------------------------------------
    void               set_device( 
        const IDWriteFactory* write_factory );

private:
    /// The DirectWrite factory.
    IDWriteFactory*    m_Direct2DWFactory = nullptr;
    /// The DirectWrite font.
    IDWriteTextFormat* m_Direct2DFont     = nullptr;
};

}

#endif
