#include <render/Font2D.hpp>
#include <render/Overlay.hpp>
using namespace render;

Font2D::Font2D(
    const std::string&    name,
    const int32_t         height,
    const int32_t         weight,
    const int32_t         flags,
    const IDWriteFactory* write_factory ) :
    Font( name, height, weight, flags )
{
    set_device( write_factory );
}

Font2D::~Font2D()
{
    DTOR_EXECUTE_VIRTUAL( shutdown );
}

void Font2D::shutdown()
{
    safe_release( &m_Direct2DFont );
}

bool Font2D::create()
{
    if( !m_Direct2DWFactory ) {
        return false;
    }

    safe_release( &m_Direct2DFont );
    return SUCCEEDED( m_Direct2DWFactory->CreateTextFormat(
        Overlay::convert_string_to_wide( m_Name ).c_str(),
        nullptr,
        static_cast<DWRITE_FONT_WEIGHT>( m_Weight ),
        DWRITE_FONT_STYLE_NORMAL,
        static_cast<DWRITE_FONT_STRETCH>( m_Flags ),
        static_cast<float>( m_Height ),
        L"en-Us",
        &m_Direct2DFont )
    ) ? true : false;
}

IDWriteTextFormat* Font2D::get_font() const
{
    return m_Direct2DFont;
}

void Font2D::set_device(
    const IDWriteFactory* write_factory )
{
    m_Direct2DWFactory = const_cast<IDWriteFactory*>( write_factory );
}
