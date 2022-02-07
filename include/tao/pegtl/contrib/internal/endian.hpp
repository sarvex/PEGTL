// Copyright (c) 2017-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INTERNAL_ENDIAN_HPP
#define TAO_PEGTL_CONTRIB_INTERNAL_ENDIAN_HPP

#include <cstring>

#if defined( _WIN32 ) && !defined( __MINGW32__ ) && !defined( __CYGWIN__ )
#include "endian_win.hpp"
#else
#include "endian_gcc.hpp"
#endif

namespace tao::pegtl::internal
{
   struct from_be
   {
      template< typename T >
      [[nodiscard]] static T from( const T n ) noexcept
      {
         return from_big_endian( n );
      }

      template< typename T >
      [[nodiscard]] static T from( const void* p ) noexcept
      {
         T n;
         std::memcpy( &n, p, sizeof( n ) );
         return from_big_endian( n );
      }
   };

   struct from_le
   {
      template< typename T >
      [[nodiscard]] static T from( const T n ) noexcept
      {
         return from_little_endian( n );
      }

      template< typename T >
      [[nodiscard]] static T from( const void* p ) noexcept
      {
         T n;
         std::memcpy( &n, p, sizeof( n ) );
         return internal::from_little_endian( n );
      }
   };

}  // namespace tao::pegtl::internal

#endif
