#include <render/Surface3D9.hpp>
using namespace drawing;
using namespace render;

class D3DVERTEX
{
public:
    D3DVERTEX() = default;

    ///-------------------------------------------------------------------------------------------------
    /// Constructor.
    ///
    /// @author Michael
    /// @date   04.03.2017
    ///
    /// @tparam T_X     Type of the x coordinate.
    /// @tparam T_Y     Type of the y coordinate.
    /// @tparam T_Z     Type of the z coordinate.
    /// @tparam T_HT    Type of the height.
    /// @param  x       The T_X to process.
    /// @param  y       The T_Y to process.
    /// @param  z       The T_Z to process.
    /// @param  ht      The height.
    /// @param  color   The color.
    ///-------------------------------------------------------------------------------------------------
    template<typename T_X, typename T_Y, typename T_Z, typename T_HT>
    D3DVERTEX( const T_X x, const T_Y y, const T_Z z, const T_HT ht, const uint32_t color )
    {
        initialize( x, y, z, ht, color );
    }

    ///-------------------------------------------------------------------------------------------------
    /// Initializes this object.
    ///
    /// @author Michael
    /// @date   04.03.2017
    ///
    /// @tparam T_X     Type of the x coordinate.
    /// @tparam T_Y     Type of the y coordinate.
    /// @tparam T_Z     Type of the z coordinate.
    /// @tparam T_HT    Type of the height.
    /// @param  x       The T_X to process.
    /// @param  y       The T_Y to process.
    /// @param  z       The T_Z to process.
    /// @param  ht      The height.
    /// @param  color   The color.
    ///-------------------------------------------------------------------------------------------------
    template<typename T_X, typename T_Y, typename T_Z, typename T_HT>
    void initialize( const T_X x, const T_Y y, const T_Z z, const T_HT ht, const uint32_t color )
    {
        static_assert( std::is_arithmetic<T_X>::value &&
                       std::is_arithmetic<T_X>::value &&
                       std::is_arithmetic<T_X>::value &&
                       std::is_arithmetic<T_X>::value,
                       "Type T has to be arithmetic" );

        m_Position.at( 0 ) = static_cast<float>( x );
        m_Position.at( 1 ) = static_cast<float>( y );
        m_Position.at( 2 ) = static_cast<float>( z );
        m_HT               = static_cast<float>( ht );
        m_Color            = color;
    }

private:
    using Pos_t = std::array<float, 3>;
public:
    Pos_t    m_Position;
    float    m_HT = 0.f;
    uint32_t m_Color;
};

Surface3D9::Surface3D9( const ID3DXSprite* sprite )
{
    set_sprite( sprite );
}

Surface3D9::~Surface3D9()
{
    /// Call to a virtual function inside a destructor will be statically resolved
    DTOR_EXECUTE_VIRTUAL( shutdown );
}

bool Surface3D9::initialize( const void* device )
{
    m_Direct3D9Device = static_cast<IDirect3DDevice9Ex*>( const_cast<void*>( device ) );
    m_Initialized     = m_Direct3D9Device != nullptr;

    return m_Initialized.load();
}

bool Surface3D9::begin_scene()
{
    if( m_Initialized.load() ) {
        m_Direct3D9Device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
        m_Direct3D9Device->SetTexture( 0, nullptr );
        m_Direct3D9Device->SetVertexShader( nullptr );
        m_Direct3D9Device->SetPixelShader( nullptr );

        m_Direct3D9Device->SetRenderState( D3DRS_LIGHTING, 0 );
        m_Direct3D9Device->SetRenderState( D3DRS_FOGENABLE, 0 );
        m_Direct3D9Device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
        m_Direct3D9Device->SetRenderState( D3DRS_ALPHATESTENABLE, 0 );
        m_Direct3D9Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
        m_Direct3D9Device->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
        m_Direct3D9Device->SetRenderState( D3DRS_SCISSORTESTENABLE, 1 );
        m_Direct3D9Device->SetRenderState( D3DRS_ZWRITEENABLE, 0 );

        m_Direct3D9Device->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
        m_Direct3D9Device->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );

        m_Direct3D9Device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
        m_Direct3D9Device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
        m_Direct3D9Device->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
        m_Direct3D9Device->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
        m_Direct3D9Device->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
        m_Direct3D9Device->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

        m_Direct3D9Device->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
        m_Direct3D9Device->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
        m_Direct3D9Device->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );

        m_Direct3D9Device->SetRenderState( D3DRS_ALPHABLENDENABLE, 1 );
        m_Direct3D9Device->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, 1 );
        m_Direct3D9Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
        m_Direct3D9Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
        m_Direct3D9Device->SetRenderState( D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA );
        m_Direct3D9Device->SetRenderState( D3DRS_DESTBLENDALPHA, D3DBLEND_ONE );

        if( FAILED( m_Direct3D9Device->BeginScene() ) ) {
            return false;
        }
    }
    return m_Initialized.load();
}

Font_t Surface3D9::add_font(
    const std::string& name,
    const std::string& definition,
    const int32_t      height,
    const int32_t      weight,
    const int32_t      flags )
{
    if( !m_Initialized.load() ||
        name.empty()          ||
        definition.empty() ) {
        return nullptr;
    }

    std::unique_lock<Mutex> lock( m_mutex );
    if( m_Fonts.count( name ) ) {
        return m_Fonts.at( name );
    }

    auto font = std::make_shared<Font3D9>(
        definition,
        height,
        weight,
        flags,
        m_Direct3D9Device
    );
    if( !font->create() ) {
        return nullptr;
    }

    m_Fonts.emplace( name, std::move( font ) );
    return m_Fonts.at( name );
}


void Surface3D9::end_scene()
{
    if( m_Initialized.load() ) {        
        render_data();
    }
}

void Surface3D9::shutdown()
{
    Surface::shutdown();
    safe_release( &m_Direct3DXSprite );
}

void Surface3D9::text(
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
    const auto message_length = static_cast<int32_t>( message.length() );
    auto direct_draw_font     = std::static_pointer_cast<Font3D9>( font );
    RECT font_rect = {
        x - message_length * direct_draw_font->height() / 4,
        y ,
        x + message_length *  direct_draw_font->height() / 2,
        y
    };
    direct_draw_font->get_font()->DrawTextA(
        nullptr,
        message.c_str(),
        message_length,
        &font_rect,
        DT_NOCLIP,
        color.to_hex()
    );
}

void Surface3D9::set_sprite( const ID3DXSprite* sprite )
{
    m_Direct3DXSprite = const_cast<ID3DXSprite*>( sprite );
}

void Surface3D9::render_data()
{
    if( !m_Initialized.load() ) {
        return;
    }

    static std::array<D3DVERTEX, 2> line_vertices;
    static std::array<D3DVERTEX, 4> rect_vertices;
    
    std::unique_lock<Mutex> lock( m_mutex );
    for( const auto& data : m_RectAngles ) {
        const auto& x  = std::get<0>( data );
        const auto& y  = std::get<1>( data );
        const auto& w  = std::get<2>( data );
        const auto& h  = std::get<3>( data );
        const auto clr = std::get<4>( data ).to_hex();

        rect_vertices.at( 0 ).initialize( x,     y,     0, 1, clr );
        rect_vertices.at( 1 ).initialize( x + w, y,     0, 1, clr );
        rect_vertices.at( 2 ).initialize( x + w, y + h, 0, 1, clr );
        rect_vertices.at( 3 ).initialize( x,     y + h, 0, 1, clr );

        m_Direct3D9Device->DrawPrimitiveUP(
            D3DPT_TRIANGLEFAN,
            2,
            rect_vertices.data(),
            sizeof( D3DVERTEX )
        );
    }
    for( const auto& data : m_Lines ) {
        const auto& start_x = std::get<0>( data );
        const auto& start_y = std::get<1>( data );
        const auto& end_x   = std::get<2>( data );
        const auto& end_y   = std::get<3>( data );
        const auto clr      = std::get<4>( data ).to_hex();

        line_vertices.at( 0 ).initialize( start_x, start_y, 0, 1, clr );
        line_vertices.at( 1 ).initialize( end_x,   end_y,   0, 1, clr );

        m_Direct3D9Device->DrawPrimitiveUP(
            D3DPT_LINELIST,
            1,
            line_vertices.data(),
            sizeof( D3DVERTEX )
        );
    }

    /// clear the old data
    m_Lines.clear();
    m_RectAngles.clear();
}
