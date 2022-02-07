// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INTERNAL_PEEK_UTF16_HPP
#define TAO_PEGTL_CONTRIB_INTERNAL_PEEK_UTF16_HPP

#include <cstddef>
#include <cstdint>

#include "../../internal/data_and_size.hpp"

#include "endian.hpp"
#include "peek_endian_impl.hpp"

namespace tao::pegtl::internal
{
   template< typename R >
   struct peek_utf16_impl
   {
      using data_t = char32_t;
      using pair_t = data_and_size< char32_t >;

      static_assert( sizeof( char16_t ) == 2 );
      static_assert( sizeof( char32_t ) == 4 );

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in ) noexcept( noexcept( in.size( 42 ) ) )
      {
         if( const auto r = peek_endian_impl< char16_t, Endian >( in ) ) {
            if( ( r.data < 0xd800 ) || ( r.data > 0xdfff ) ) {
               return r;
            }
            if( r.data < 0xdc00 ) {
               if( const auto s = peek_endian_impl< char16_t, Endian >( in, r.size ) ) {
                  if( ( s.data >= 0xdc00 ) && ( s.data <= 0xdfff ) ) {
                     return { ( ( char32_t( r.data & 0x03ff ) << 10 ) | char32_t( s.data & 0x03ff ) ) + 0x10000, r.size + s.size };
                  }
               }
            }
         }
         return { 0, 0 };
      }
   };

   using peek_utf16_be = peek_utf16_impl< from_be >;
   using peek_utf16_le = peek_utf16_impl< from_le >;

}  // namespace tao::pegtl::internal

#endif
