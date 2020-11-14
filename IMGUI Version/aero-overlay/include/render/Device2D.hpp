#pragma once
#ifndef REACTIION_AERO_OVERLAY_DEVICE2D_HPP
#define REACTIION_AERO_OVERLAY_DEVICE2D_HPP
#include "Overlay.hpp"
#include "Surface2D.hpp"

namespace render {

class Device2D :
    public Overlay
{
public:
    ///-------------------------------------------------------------------------------------------------
    /// Default constructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    Device2D() = default;

    ///-------------------------------------------------------------------------------------------------
    /// Destructor.
    ///
    /// @author ReactiioN
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    ~Device2D() override;

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
    /// The Direct2D factory.
    ID2D1Factory*          m_Direct2DFactory          = nullptr;
    /// The Direct2D render target.
    ID2D1HwndRenderTarget* m_Direct2DHwndRenderTarget = nullptr;
    /// The Direct Write factory.
    IDWriteFactory*        m_DirectWriteFactory       = nullptr;
    /// The Direct2D color brush.
    ID2D1SolidColorBrush*  m_Diect2DColorBrush        = nullptr;
};

}

#endif
