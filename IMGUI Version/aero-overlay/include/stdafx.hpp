#pragma once
#ifndef REACTIION_AERO_OVERLAY_HPP
#define REACTIION_AERO_OVERLAY_HPP
#include <Windows.h>

#include <dwmapi.h>
#pragma comment( lib, "dwmapi.lib" )

/// std::arry
#include <array>
/// std::atomic<T>
#include <atomic>
/// std::transform, std::find, ...
#include <algorithm>
/// std::wstring_converter
#include <codecvt>
/// std::fstream
#include <fstream>
/// std::cout, std::cin
#include <iostream>
/// std::map
#include <map>
/// std::shared_ptr, std::unique_ptr
#include <memory>
/// std::random_device
#include <random>
/// std::stringstream, stream << operator for strings
#include <sstream>
/// std::shared_timed_mutex, std::unique_lock, std::shared_lock
#include <shared_mutex>
/// std::tuple
#include <tuple>
/// std::this_thread::sleep_for
#include <thread>
/// std::vector
#include <vector>

///-------------------------------------------------------------------------------------------------
/// Safe release.
///
/// @author ReactiioN
/// @date   04.03.2017
///
/// @tparam T   Generic type parameter.
/// @param [in,out] interface_to_release    If non-null, the interface to release.
///-------------------------------------------------------------------------------------------------
template<typename T>
void safe_release( T** interface_to_release )
{
    if( interface_to_release && *interface_to_release ) {
        ( *interface_to_release )->Release();
        ( *interface_to_release ) = nullptr;
    }
}

///-------------------------------------------------------------------------------------------------
/// A macro that defines Destructor execute virtual.
///
/// @author ReactiioN
/// @date   04.03.2017
///
/// @param  FN  The function.
///-------------------------------------------------------------------------------------------------
#define DTOR_EXECUTE_VIRTUAL( FN ) [this]{ \
        FN(); \
    }

#endif
