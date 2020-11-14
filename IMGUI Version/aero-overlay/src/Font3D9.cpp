#include <render/Font3D9.hpp>
using namespace render;

Font3D9::Font3D9(
    const std::string&        name,
    const int32_t             height,
    const int32_t             weight,
    const int32_t             flags,
    const IDirect3DDevice9Ex* device ) :
    Font( name, height, weight, flags )
{
    set_device( device );
}

Font3D9::~Font3D9()
{
    DTOR_EXECUTE_VIRTUAL( shutdown );
}

void Font3D9::shutdown()
{
    safe_release( &m_Direct3DXFont );
}

bool Font3D9::create()
{
    if( !m_Direct3D9Device ) {
        return false;
    }

    /// release previous data
    safe_release( &m_Direct3DXFont );
    return SUCCEEDED( D3DXCreateFontA( m_Direct3D9Device,
                                       m_Height,
                                       0U,
                                       static_cast<uint32_t>( m_Weight ),
                                       1U,
                                       FALSE,
                                       DEFAULT_CHARSET,
                                       OUT_DEFAULT_PRECIS,
                                       m_Flags,
                                       DEFAULT_PITCH | FF_DONTCARE,
                                       m_Name.c_str(),
                                       &m_Direct3DXFont )
    ) ? true : false;    
}

ID3DXFont* Font3D9::get_font() const
{
    return m_Direct3DXFont;
}

void Font3D9::set_device( 
    const IDirect3DDevice9Ex* device )
{
    m_Direct3D9Device = const_cast<IDirect3DDevice9Ex*>( device );
}
