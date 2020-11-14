#include <render/Surface.hpp>
using namespace drawing;
using namespace render;

Surface::~Surface()
{
}

Font_t Surface::get_font(
    const std::string& name )
{
    std::shared_lock<Mutex> lock( m_mutex );
    return !name.empty() && m_Fonts.count( name ) != 0 
         ? m_Fonts.at( name )
         : nullptr;
}

void Surface::shutdown()
{
    std::unique_lock<Mutex> lock( m_mutex );
    for( auto& kp : m_Fonts ) {
        kp.second->shutdown();
    }
    m_Fonts.clear();
}

void Surface::border_box(
    const int32_t x,
    const int32_t y,
    const int32_t w,
    const int32_t h,
    const int32_t thickness,
    const Color&  color )
{
    insert_rect_angle( x,     y,     w,             thickness, color );
    insert_rect_angle( x,     y,     thickness,     h,         color );
    insert_rect_angle( x + w, y,     thickness,     h,         color );
    insert_rect_angle( x,     y + h, w + thickness, thickness, color );
}

void Surface::border_box_outlined(
    const int32_t x,
    const int32_t y,
    const int32_t w,
    const int32_t h,
    const int32_t thickness,
    const Color&  color,
    const Color&  outlined,
    const int32_t thickness_outline )
{
    border_box( x, y, w, h, thickness, color );
    border_box(
        x - thickness_outline,
        y - thickness_outline,
        w + thickness + thickness_outline,
        h + thickness + thickness_outline,
        thickness_outline,
        outlined
    );
    border_box(
        x + thickness,
        y + thickness,
        w - thickness - thickness_outline,
        h - thickness - thickness_outline,
        thickness_outline,
        outlined
    );
}

void Surface::rect(
    const int32_t x,
    const int32_t y,
    const int32_t w,
    const int32_t h,
    const Color&  color )
{
    insert_rect_angle( x, y, w, h, color );
}

void Surface::rect_outlined(
    const int32_t x,
    const int32_t y,
    const int32_t w,
    const int32_t h,
    const int32_t thickness,
    const Color&  color,
    const Color&  outlined )
{
    insert_rect_angle( x, y, w, h, color );
    border_box( x - thickness,
                y - thickness,
                w + thickness,
                h + thickness,
                thickness,
                outlined
    );
}

void Surface::line(
    const int32_t start_x,
    const int32_t start_y,
    const int32_t end_x,
    const int32_t end_y,
    const Color&  color )
{
    insert_line( start_x, start_y, end_x, end_y, color );
}

void Surface::text(
    const int32_t      x,
    const int32_t      y,
    const std::string& font_name,
    const Color&       color,
    const std::string& message )
{
    if( m_Initialized.load() ) {
        auto font = get_font( font_name );
        if( font ) {
            text( x, y, font, color, message );
        }
    }
}
