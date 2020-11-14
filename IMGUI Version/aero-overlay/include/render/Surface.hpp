#pragma once
#ifndef REACTIION_AERO_OVERLAY_SURFACE_HPP
#define REACTIION_AERO_OVERLAY_SURFACE_HPP

#include "../drawing/Color.hpp"
#include "Font.hpp"

namespace render {

class Surface
{
public:
    /// An alias for the mutex.
    using Mutex = std::shared_timed_mutex;
    /// The maximum render elements.
    static constexpr size_t MAX_RENDER_ELEMENTS = 512;

private:
    /// An typedef for the render object
    using RenderObj  = std::tuple<
        int32_t,       /// x position
        int32_t,       /// y position
        int32_t,       /// width
        int32_t,       /// height
        drawing::Color /// obv. the color
    >;

    /// An alias for the map of fonts.
    using Fonts      = std::map<std::string, Font_t>;
    /// An alias for the render objects.
    using RenderData = std::vector<RenderObj>;    

public:
    ///-------------------------------------------------------------------------------------------------
    /// Default constructor.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    Surface() = default;

    ///-------------------------------------------------------------------------------------------------
    /// Destructor.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual ~Surface();

    ///-------------------------------------------------------------------------------------------------
    /// Initializes this object.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  device  The device.
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool initialize(
        const void*        device ) = 0;

    ///-------------------------------------------------------------------------------------------------
    /// Begins a scene.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool begin_scene() = 0;

    ///-------------------------------------------------------------------------------------------------
    /// Adds a font.
    ///
    /// @author Michael
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
    virtual Font_t add_font(
        const std::string& name,
        const std::string& definition,
        const int32_t      height,
        const int32_t      weight,
        const int32_t      flags ) = 0;

    ///-------------------------------------------------------------------------------------------------
    /// Gets a font.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  name    The name.
    ///
    /// @return The font.
    ///-------------------------------------------------------------------------------------------------
    virtual Font_t get_font(
        const std::string&  name );

protected:
    ///-------------------------------------------------------------------------------------------------
    /// Renders the data.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual void render_data() = 0;

public:
    ///-------------------------------------------------------------------------------------------------
    /// Ends a scene.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual void end_scene() = 0;

    ///-------------------------------------------------------------------------------------------------
    /// Shuts down this object and frees any resources it is using.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual void shutdown();

    ///-------------------------------------------------------------------------------------------------
    /// Renders a border box.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  x           The int32_t to process.
    /// @param  y           The int32_t to process.
    /// @param  w           The int32_t to process.
    /// @param  h           The int32_t to process.
    /// @param  thickness   The thickness.
    /// @param  color       The color.
    ///-------------------------------------------------------------------------------------------------
    virtual void border_box(
        const int32_t         x,
        const int32_t         y,
        const int32_t         w,
        const int32_t         h,
        const int32_t         thickness,
        const drawing::Color& color );

    ///-------------------------------------------------------------------------------------------------
    /// Renders an outlined border box.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  x                   The int32_t to process.
    /// @param  y                   The int32_t to process.
    /// @param  w                   The int32_t to process.
    /// @param  h                   The int32_t to process.
    /// @param  thickness           The thickness.
    /// @param  color               The color.
    /// @param  outlined            (Optional) The outlined.
    /// @param  thickness_outline   (Optional) The thickness outline.
    ///-------------------------------------------------------------------------------------------------

    virtual void border_box_outlined(
        const int32_t         x,
        const int32_t         y,
        const int32_t         w,
        const int32_t         h,
        const int32_t         thickness,
        const drawing::Color& color,
        const drawing::Color& outlined  = 0xFF000000,
        const int32_t         thickness_outline = 1 );

    ///-------------------------------------------------------------------------------------------------
    /// Renders a rectangles.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  x       The int32_t to process.
    /// @param  y       The int32_t to process.
    /// @param  w       The int32_t to process.
    /// @param  h       The int32_t to process.
    /// @param  color   The color.
    ///-------------------------------------------------------------------------------------------------
    virtual void rect(
        const int32_t         x,
        const int32_t         y,
        const int32_t         w,
        const int32_t         h,
        const drawing::Color& color );

    ///-------------------------------------------------------------------------------------------------
    /// Renders an outlined rectangle.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  x           The int32_t to process.
    /// @param  y           The int32_t to process.
    /// @param  w           The int32_t to process.
    /// @param  h           The int32_t to process.
    /// @param  thickness   The thickness.
    /// @param  color       The color.
    /// @param  outlined    (Optional) The outlined.
    ///-------------------------------------------------------------------------------------------------
    virtual void rect_outlined(
        const int32_t         x,
        const int32_t         y,
        const int32_t         w,
        const int32_t         h,
        const int32_t         thickness,
        const drawing::Color& color,
        const drawing::Color& outlined = 0xFF000000 );

    ///-------------------------------------------------------------------------------------------------
    /// Renders a line.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  start_x The start x coordinate.
    /// @param  start_y The start y coordinate.
    /// @param  end_x   The end x coordinate.
    /// @param  end_y   The end y coordinate.
    /// @param  color   The color.
    ///-------------------------------------------------------------------------------------------------
    virtual void line(
        const int32_t         start_x,
        const int32_t         start_y,
        const int32_t         end_x,
        const int32_t         end_y,
        const drawing::Color& color );

    ///-------------------------------------------------------------------------------------------------
    /// Renders a text.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  x       The int32_t to process.
    /// @param  y       The int32_t to process.
    /// @param  font    The font.
    /// @param  color   The color.
    /// @param  message The message.
    ///-------------------------------------------------------------------------------------------------
    virtual void text(
        const int32_t         x,
        const int32_t         y,
        const Font_t&         font,
        const drawing::Color& color,
        const std::string&    message ) = 0;

    ///-------------------------------------------------------------------------------------------------
    /// Renders a text.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  x           The int32_t to process.
    /// @param  y           The int32_t to process.
    /// @param  font_name   Name of the font.
    /// @param  color       The color.
    /// @param  message     The message.
    ///-------------------------------------------------------------------------------------------------
    virtual void text(
        const int32_t         x,
        const int32_t         y,
        const std::string&    font_name,
        const drawing::Color& color,
        const std::string&    message );

protected:
    ///-------------------------------------------------------------------------------------------------
    /// Inserts a line.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @tparam T1  Generic type parameter.
    /// @tparam T2  Generic type parameter.
    /// @tparam T3  Generic type parameter.
    /// @tparam T4  Generic type parameter.
    /// @param  start_x The start x coordinate.
    /// @param  start_y The start y coordinate.
    /// @param  end_x   The end x coordinate.
    /// @param  end_y   The end y coordinate.
    /// @param  color   The color.
    ///-------------------------------------------------------------------------------------------------
    template<typename T1, typename T2, typename T3, typename T4>
    void insert_line(
        const T1              start_x,
        const T2              start_y,
        const T3              end_x,
        const T4              end_y,
        const drawing::Color& color );

    ///-------------------------------------------------------------------------------------------------
    /// Inserts a rectangle.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @tparam T1  Generic type parameter.
    /// @tparam T2  Generic type parameter.
    /// @tparam T3  Generic type parameter.
    /// @tparam T4  Generic type parameter.
    /// @param  x       The T1 to process.
    /// @param  y       The T2 to process.
    /// @param  w       The T3 to process.
    /// @param  h       The T4 to process.
    /// @param  color   The color.
    ///-------------------------------------------------------------------------------------------------
    template<typename T1, typename T2, typename T3, typename T4>
    void insert_rect_angle(
        const T1              x,
        const T2              y,
        const T3              w,
        const T4              h,
        const drawing::Color& color );

protected:
    std::atomic_bool m_Initialized = false;
    RenderData    m_Lines;
    RenderData    m_RectAngles;
    Fonts         m_Fonts;
    mutable Mutex m_mutex;
};

template<typename T1, typename T2, typename T3, typename T4>
void Surface::insert_line(
    const T1              start_x,
    const T2              start_y,
    const T3              end_x,
    const T4              end_y,
    const drawing::Color& color )
{
    static_assert( std::is_arithmetic<T1>::value, "Type T1 has to be arithmetic" );
    static_assert( std::is_arithmetic<T2>::value, "Type T2 has to be arithmetic" );
    static_assert( std::is_arithmetic<T3>::value, "Type T3 has to be arithmetic" );
    static_assert( std::is_arithmetic<T4>::value, "Type T4 has to be arithmetic" );

    std::unique_lock<Mutex> lock( m_mutex );
    if( m_Lines.size() >= MAX_RENDER_ELEMENTS - 1 ) {
        render_data();
    }

    m_Lines.push_back( 
        std::make_tuple(
            static_cast<int32_t>( start_x ),
            static_cast<int32_t>( start_y ),
            static_cast<int32_t>( end_x ),
            static_cast<int32_t>( end_y ),
            color
        )
    );
}

template<typename T1, typename T2, typename T3, typename T4>
void Surface::insert_rect_angle(
    const T1              x,
    const T2              y,
    const T3              w,
    const T4              h,
    const drawing::Color& color )
{
    static_assert( std::is_arithmetic<T1>::value, "Type T1 has to be arithmetic" );
    static_assert( std::is_arithmetic<T2>::value, "Type T2 has to be arithmetic" );
    static_assert( std::is_arithmetic<T3>::value, "Type T3 has to be arithmetic" );
    static_assert( std::is_arithmetic<T4>::value, "Type T4 has to be arithmetic" );

    std::unique_lock<Mutex> lock( m_mutex );
    if( m_RectAngles.size() >= MAX_RENDER_ELEMENTS - 1 ) {
        render_data();
    }

    m_RectAngles.push_back( 
        std::make_tuple(
            static_cast<int32_t>( x ),
            static_cast<int32_t>( y ),
            static_cast<int32_t>( w ),
            static_cast<int32_t>( h ),
            color
        )
    );
}

}

#endif
