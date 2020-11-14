#pragma once
#ifndef REACTIION_AERO_OVERLAY_FONT_HPP
#define REACTIION_AERO_OVERLAY_FONT_HPP
#include "../stdafx.hpp"

namespace render {

class Font
{
public:
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
    ///-------------------------------------------------------------------------------------------------
    Font(
        const std::string& name,
        const int32_t      height,
        const int32_t      weight,
        const int32_t      flags );
    ///-------------------------------------------------------------------------------------------------
    /// Destructor.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual ~Font();

    ///-------------------------------------------------------------------------------------------------
    /// Shuts down this object and frees any resources it is using.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual void              shutdown() = 0;

protected:
    ///-------------------------------------------------------------------------------------------------
    /// Initializes this object.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool              create() = 0;

public:
    ///-------------------------------------------------------------------------------------------------
    /// Gets the height.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @return An int32_t.
    ///-------------------------------------------------------------------------------------------------
    inline int32_t            height() const;

    ///-------------------------------------------------------------------------------------------------
    /// Gets the weight.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @return An int32_t.
    ///-------------------------------------------------------------------------------------------------
    inline int32_t            weight() const;

    ///-------------------------------------------------------------------------------------------------
    /// Gets the flags.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @return An int32_t.
    ///-------------------------------------------------------------------------------------------------
    inline int32_t            flags() const;

    ///-------------------------------------------------------------------------------------------------
    /// Gets the name.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @return A reference to a const std::string.
    ///-------------------------------------------------------------------------------------------------
    inline const std::string& name() const;

protected:
    /// The name.
    std::string m_Name;
    /// The height.
    int32_t     m_Height = 0;
    /// The weight.
    int32_t     m_Weight = 0;
    /// The flags.
    int32_t     m_Flags  = 0;    
};

inline Font::Font( 
    const std::string& name,
    const int32_t      height,
    const int32_t      weight,
    const int32_t      flags ) :
    m_Name( name ),
    m_Height( height ),
    m_Weight( weight ),
    m_Flags( flags )
{
}

inline Font::~Font()
{    
}

inline int32_t Font::height() const
{
    return m_Height;
}

inline int32_t Font::weight() const
{
    return m_Weight;
}

inline int32_t Font::flags() const
{
    return m_Flags;
}

const std::string& Font::name() const
{
    return m_Name;
}

/// An alias for a shared_ptr of the type class Font.
using Font_t = std::shared_ptr<Font>;

}

#endif
