#include <render/Surface2D.hpp>
#include "render/Overlay.hpp"
using namespace drawing;
using namespace render;

Surface2D::~Surface2D()
{
    /// Call to a virtual function inside a destructor will be statically resolved
    DTOR_EXECUTE_VIRTUAL( shutdown );
}

Surface2D::Surface2D(
    const IDWriteFactory*       write_factory,
    const ID2D1SolidColorBrush* color_brush )
{
    set_write_factory( write_factory );
    set_color_brush( color_brush );
}

bool Surface2D::initialize( const void* device )
{
    if( device ) {
        m_Direct2DHwndRenderTarget = static_cast<ID2D1HwndRenderTarget*>(
            const_cast<void*>( device )
        );
    }
    m_Initialized = m_Diect2DColorBrush &&
        m_DirectWriteFactory &&
        m_Direct2DHwndRenderTarget;

    return m_Initialized.load();
}

bool Surface2D::begin_scene()
{
    return m_Initialized.load();
}

Font_t Surface2D::add_font(
    const std::string& name,
    const std::string& definition,
    const int32_t      height,
    const int32_t      weight,
    const int32_t      flags )
{
    if( !m_Initialized.load() ||
        name.empty()   ||
        definition.empty() ) {
        return nullptr;
    }

    std::unique_lock<Mutex> lock( m_mutex );
    if( m_Fonts.count( name ) ) {
        return m_Fonts.at( name );
    }

    auto font = std::make_shared<Font2D>(
        definition,
        height,
        weight,
        flags,
        m_DirectWriteFactory
    );
    if( !font->create() ) {
        return nullptr;
    }

    m_Fonts.emplace( name, std::move( font ) );
    return m_Fonts.at( name );
}

void Surface2D::end_scene()
{
    if( m_Initialized.load() ) {
        render_data();
    }
}

void Surface2D::shutdown()
{
    Surface::shutdown();
    safe_release( &m_Direct2DHwndRenderTarget );
    safe_release( &m_DirectWriteFactory );
    safe_release( &m_Diect2DColorBrush );
}

void Surface2D::text(
    const int32_t      x,
    const int32_t      y,
    const Font_t&      font,
    const Color&       color,
    const std::string& message )
{
    if( !m_Initialized.load() || !font || message.empty() ) {
        return;
    }

    render_data();
    auto direct_draw_font = std::static_pointer_cast<Font2D>( font );
    
    const auto X = static_cast<float>( x );
    const auto Y = static_cast<float>( y );
    const auto font_rect = D2D1::RectF(
        X,
        Y,
        X + static_cast<float>( message.length() ) * static_cast<float>( direct_draw_font->height() / 2 ),
        static_cast<float>( direct_draw_font->height() )
    );

    /// convert the message to an unicode string
    const auto message_unicode = Overlay::convert_string_to_wide( message );

    m_Diect2DColorBrush->SetColor( D2D1::ColorF( color.to_hex() ) );
    m_Direct2DHwndRenderTarget->DrawTextW( 
        message_unicode.c_str(),
        static_cast<uint32_t>( message_unicode.length() ),
        direct_draw_font->get_font(),
        &font_rect,
        m_Diect2DColorBrush 
    );
}

void Surface2D::set_render_target(
    const ID2D1HwndRenderTarget* render_target )
{
    m_Direct2DHwndRenderTarget = const_cast<ID2D1HwndRenderTarget*>( render_target );
}

void Surface2D::set_write_factory(
    const IDWriteFactory* write_factory )
{
    m_DirectWriteFactory = const_cast<IDWriteFactory*>( write_factory );
}

void Surface2D::set_color_brush(
    const ID2D1SolidColorBrush* color_brush )
{
    m_Diect2DColorBrush = const_cast<ID2D1SolidColorBrush*>( color_brush );
}

void Surface2D::render_data()
{
    if( !m_Initialized.load() ) {
        return;
    }

    std::unique_lock<Mutex> lock( m_mutex );
    for( const auto& data : m_RectAngles ) {
        const auto& x   = static_cast<float>( std::get<0>( data ) );
        const auto& y   = static_cast<float>( std::get<1>( data ) );
        const auto& w   = static_cast<float>( std::get<2>( data ) );
        const auto& h   = static_cast<float>( std::get<3>( data ) );
        const auto clr  = std::get<4>( data ).to_hex();
        const auto rect = D2D1::RectF( x, y, x + w, y + h );
        m_Diect2DColorBrush->SetColor( D2D1::ColorF( clr ) );
        m_Direct2DHwndRenderTarget->FillRectangle( &rect, m_Diect2DColorBrush );
    }
    for( const auto& data : m_Lines ) {
        const auto& start_x = static_cast<float>( std::get<0>( data ) );
        const auto& start_y = static_cast<float>( std::get<1>( data ) );
        const auto& end_x   = static_cast<float>( std::get<2>( data ) );
        const auto& end_y   = static_cast<float>( std::get<3>( data ) );
        const auto clr      = std::get<4>( data ).to_hex();
        
        m_Diect2DColorBrush->SetColor( D2D1::ColorF( clr ) );
        m_Direct2DHwndRenderTarget->DrawLine(
            {
                start_x,
                start_y,
            },
            {
                end_x,
                end_y,
            },
            m_Diect2DColorBrush
        );
    }

    /// clear the old data
    m_Lines.clear();
    m_RectAngles.clear();
}
