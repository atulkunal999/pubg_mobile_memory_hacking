#include <drawing/Color.hpp>
using namespace drawing;

Color::Color()
{
    m_Color.fill( 255 );
}

Color::Color( const Color_t& color ) :
    m_Color( color )
{
}

Color::Color( const uint32_t color )
{
    set( color );
}

Color& Color::operator = ( const Color& color )
{
    set( color.to_hex() );
    return *this;
}

Color& Color::operator = ( const uint32_t color )
{
    set( color );
    return *this;
}

bool Color::operator == ( const Color& color ) const
{
    return to_hex() == color.to_hex();
}

bool Color::operator == ( const uint32_t color ) const
{
    return to_hex() == color;
}

bool Color::operator != ( const Color& color ) const
{
    return !( *this == color );
}

bool Color::operator != ( const uint32_t  color ) const
{
    return !( *this == color );
}

uint8_t& Color::operator [] ( const size_t index )
{
    return m_Color[ index ];
}

const uint8_t& Color::operator [] ( const size_t index ) const
{
    return m_Color[ index ];
}

uint8_t& Color::operator () ( const size_t index )
{
    return at( index );
}

const uint8_t& Color::operator () ( const size_t index ) const
{
    return at( index );
}

uint8_t& Color::at( const size_t index )
{
    return m_Color.at( std::clamp( index,
                                   static_cast<size_t>( 0 ),
                                   static_cast<size_t>( 3 ) )
    );
}

const uint8_t& Color::at( const size_t index ) const
{
    return m_Color.at( std::clamp( index,
                                   static_cast<size_t>( 0 ),
                                   static_cast<size_t>( 3 ) )
    );
}

Color Color::operator + ( const Color& color )
{
    Color_t buf;
    for( size_t i = 0; i < 4; ++i ) {
        buf.at( i ) = std::clamp( at( i ) + color( i ), 0, 255 );
    }
    return Color( buf );
}

Color& Color::operator += ( const Color& color )
{
    for( size_t i = 0; i < 4; ++i ) {
        at( i ) = std::clamp( at( i ) + color( i ), 0, 255 );
    }
    return *this;
}

Color Color::operator - ( const Color& color )
{
    Color_t buf;
    for( size_t i = 0; i < 4; ++i ) {
        buf.at( i ) = std::clamp( at( i ) - color( i ), 0, 255 );
    }
    return Color( buf );
}

Color& Color::operator -= ( const Color& color )
{
    for( size_t i = 0; i < 4; ++i ) {
        at( i ) = std::clamp( at( i ) - color( i ), 0, 255 );
    }
    return *this;
}

uint32_t Color::to_hex() const
{
    return static_cast<uint32_t>( at( 3 ) << 24 |
                                  at( 0 ) << 16 |
                                  at( 1 ) <<  8 |
                                  at( 2 ) );
}

void Color::set( const uint32_t color )
{
    at( 3 ) = static_cast<uint8_t>( color >> 24 & 0xFF );
    at( 0 ) = static_cast<uint8_t>( color >> 16 & 0xFF );
    at( 1 ) = static_cast<uint8_t>( color >>  8 & 0xFF );
    at( 2 ) = static_cast<uint8_t>( color       & 0xFF );
}
