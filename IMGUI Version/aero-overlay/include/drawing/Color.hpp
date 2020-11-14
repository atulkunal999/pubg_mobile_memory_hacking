#pragma once
#ifndef REACTIION_AERO_OVERLAY_COLOR_HPP
#define REACTIION_AERO_OVERLAY_COLOR_HPP
#include "../stdafx.hpp"

namespace drawing {

class Color
{
    using Color_t = std::array<uint8_t, 4>;
public:
    ///-------------------------------------------------------------------------------------------------
    /// Default constructor.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///-------------------------------------------------------------------------------------------------
    Color();

    ///-------------------------------------------------------------------------------------------------
    /// Constructor.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///-------------------------------------------------------------------------------------------------
    Color( const Color_t& color );

    ///-------------------------------------------------------------------------------------------------
    /// Constructor.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///-------------------------------------------------------------------------------------------------
    Color( const uint32_t color );

    ///-------------------------------------------------------------------------------------------------
    /// Assignment operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///
    /// @return A shallow copy of this object.
    ///-------------------------------------------------------------------------------------------------
    Color&         operator = ( const Color& color );

    ///-------------------------------------------------------------------------------------------------
    /// Assignment operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///
    /// @return A shallow copy of this object.
    ///-------------------------------------------------------------------------------------------------
    Color&         operator = ( const uint32_t color );

    ///-------------------------------------------------------------------------------------------------
    /// Equality operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///
    /// @return True if the parameters are considered equivalent.
    ///-------------------------------------------------------------------------------------------------
    bool           operator == ( const Color& color ) const;

    ///-------------------------------------------------------------------------------------------------
    /// Equality operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///
    /// @return True if the parameters are considered equivalent.
    ///-------------------------------------------------------------------------------------------------
    bool           operator == ( const uint32_t color ) const;

    ///-------------------------------------------------------------------------------------------------
    /// Inequality operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///
    /// @return True if the parameters are not considered equivalent.
    ///-------------------------------------------------------------------------------------------------
    bool           operator != ( const Color& color ) const;

    ///-------------------------------------------------------------------------------------------------
    /// Inequality operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///
    /// @return True if the parameters are not considered equivalent.
    ///-------------------------------------------------------------------------------------------------
    bool           operator != ( const uint32_t color ) const;

    ///-------------------------------------------------------------------------------------------------
    /// Array indexer operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  index   Zero-based index of the.
    ///
    /// @return The indexed value.
    ///-------------------------------------------------------------------------------------------------
    uint8_t&       operator [] ( const size_t index );

    ///-------------------------------------------------------------------------------------------------
    /// Array indexer operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  index   Zero-based index of the.
    ///
    /// @return The indexed value.
    ///-------------------------------------------------------------------------------------------------
    const uint8_t& operator [] ( const size_t index ) const;

    ///-------------------------------------------------------------------------------------------------
    /// Function call operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @return The result of the operation.
    ///-------------------------------------------------------------------------------------------------
    uint8_t&       operator () ( const size_t index );

    ///-------------------------------------------------------------------------------------------------
    /// Function call operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @return The result of the operation.
    ///-------------------------------------------------------------------------------------------------
    const uint8_t& operator () ( const size_t index ) const;

    ///-------------------------------------------------------------------------------------------------
    /// Ats the given index.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  index   Zero-based index of the.
    ///
    /// @return A reference to an uint8_t.
    ///-------------------------------------------------------------------------------------------------
    uint8_t&       at( const size_t index );

    ///-------------------------------------------------------------------------------------------------
    /// Ats the given index.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  index   Zero-based index of the.
    ///
    /// @return A reference to a const uint8_t.
    ///-------------------------------------------------------------------------------------------------
    const uint8_t& at( const size_t index ) const;

    ///-------------------------------------------------------------------------------------------------
    /// Addition operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///
    /// @return The result of the operation.
    ///-------------------------------------------------------------------------------------------------
    Color          operator + ( const Color& color );

    ///-------------------------------------------------------------------------------------------------
    /// Addition assignment operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///
    /// @return The result of the operation.
    ///-------------------------------------------------------------------------------------------------
    Color&         operator += ( const Color& color );

    ///-------------------------------------------------------------------------------------------------
    /// Subtraction operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///
    /// @return The result of the operation.
    ///-------------------------------------------------------------------------------------------------
    Color          operator - ( const Color& color );

    ///-------------------------------------------------------------------------------------------------
    /// Subtraction assignment operator.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color.
    ///
    /// @return The result of the operation.
    ///-------------------------------------------------------------------------------------------------
    Color&         operator -= ( const Color& color );

    ///-------------------------------------------------------------------------------------------------
    /// Gets the color code as hexadecimal.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @return An uint32_t.
    ///-------------------------------------------------------------------------------------------------
    uint32_t       to_hex() const;

    ///-------------------------------------------------------------------------------------------------
    /// Sets the given color as hex deciam.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @param  color   The color to set.
    ///-------------------------------------------------------------------------------------------------
    void           set( const uint32_t color );

    ///-------------------------------------------------------------------------------------------------
    /// Sets the RGBA channel.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @tparam T   Generic type parameter.
    /// @param  R   The Red channel.
    /// @param  G   The Green channel
    /// @param  B   The Blue channel.
    /// @param  A   (Optional) The Alpha channel.
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    void           set( const T R, const T G, const T B, const T A = static_cast<T>( 255 ) );

    ///-------------------------------------------------------------------------------------------------
    /// Constructor.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @tparam T   Generic type parameter.
    /// @param  R   The T to process.
    /// @param  G   The T to process.
    /// @param  B   The T to process.
    /// @param  A   (Optional) The T to process.
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    Color( const T R, const T G, const T B, const T A = static_cast<T>( 255 ) );

    ///-------------------------------------------------------------------------------------------------
    /// Gets the red channel.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @tparam T   Generic type parameter.
    ///
    /// @return The red channel as type T.
    ///-------------------------------------------------------------------------------------------------
    template<typename T = int32_t>
    T r() const;

    ///-------------------------------------------------------------------------------------------------
    /// Gets the green channel.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @tparam T   Generic type parameter.
    ///
    /// @return The green channel as type T.
    ///-------------------------------------------------------------------------------------------------
    template<typename T = int32_t>
    T g() const;

    ///-------------------------------------------------------------------------------------------------
    /// Gets the blue channel.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @tparam T   Generic type parameter.
    ///
    /// @return The blue channel as type T.
    ///-------------------------------------------------------------------------------------------------

    template<typename T = int32_t>
    T b() const;

    ///-------------------------------------------------------------------------------------------------
    /// Gets alpha channel.
    ///
    /// @author ReactiioN
    /// @date   04.03.2017
    ///
    /// @tparam T   Generic type parameter.
    ///
    /// @return The alpha channel as type T.
    ///-------------------------------------------------------------------------------------------------

    template<typename T = int32_t>
    T a() const;

private:
    Color_t m_Color;
};

template<typename T>
Color::Color( const T R, const T G, const T B, const T A )
{
    set( R, G, B, A );
}

template<typename T>
void Color::set( const T R, const T G, const T B, const T A )
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );

    const auto mins = static_cast<T>( 0 );
    const auto maxs = static_cast<T>( 255 );
    at( 0 ) = static_cast<uint8_t>( std::clamp( R, mins, maxs ) );
    at( 1 ) = static_cast<uint8_t>( std::clamp( G, mins, maxs ) );
    at( 2 ) = static_cast<uint8_t>( std::clamp( B, mins, maxs ) );
    at( 3 ) = static_cast<uint8_t>( std::clamp( A, mins, maxs ) );
}

template<typename T>
T Color::r() const
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    return static_cast<T>( at( 0 ) );
}

template<typename T>
T Color::g() const
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    return static_cast<T>( at( 1 ) );
}

template<typename T>
T Color::b() const
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    return static_cast<T>( at( 2 ) );
}

template<typename T>
T Color::a() const
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    return static_cast<T>( at( 3 ) );
}

}

#endif
